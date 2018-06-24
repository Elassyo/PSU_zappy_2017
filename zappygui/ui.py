import random
import sys
import time

from sdl2 import *
from sdl2.sdlimage import *
from sdl2.sdlttf import *
from sdl2.sdlmixer import *

from .client import Client

client = None

class Surface:

    def __init__(self, path):
        self.path = path
        rwops = SDL_RWFromFile(path.encode(), b'r')
        self.surface = IMG_Load_RW(rwops, True)
        if not self.surface:
            raise Exception('Failed to load image %s' % path)
        self.w = self.surface.contents.w
        self.h = self.surface.contents.h

    def __del__(self):
        SDL_FreeSurface(self.surface)


class Texture(Surface):

        def __init__(self, renderer, path):
            Surface.__init__(self, path)
            self.texture = SDL_CreateTextureFromSurface(renderer, self.surface)

        def __del__(self):
            SDL_DestroyTexture(self.texture)
            Surface.__del__(self)


class Sprite:

    def __init__(self, texture, x, y, scale=1.0, rotation=0.0):
        self.texture = texture
        self.x = x
        self.y = y
        self.scale = scale
        self.rotation = rotation

    def draw(self, renderer):
        rect = SDL_Rect(round(self.x), round(self.y),
            round(self.scale * self.texture.w),
            round(self.scale * self.texture.h))
        SDL_RenderCopyEx(renderer, self.texture.texture,
            None, rect, self.rotation, None, SDL_FLIP_NONE)


class Font:

    def __init__(self, path, size):
        rwops = SDL_RWFromFile(path.encode(), b'r')
        self.font = TTF_OpenFontRW(rwops, True, size)

    def __del__(self):
        TTF_CloseFont(self.font)


class Label:

    def __init__(self, renderer, font, text, x, y, scale=1.0, rotation=0.0,
            color=SDL_Color(0, 0, 0), centered=False):
        self.renderer = renderer
        self.font = font
        self.x = x
        self.y = y
        self.scale = scale
        self.rotation = rotation
        self.color = color
        self.centered = centered
        self.surface = None
        self.texture = None
        self.setText(text)

    def __del__(self):
        SDL_DestroyTexture(self.texture)
        SDL_FreeSurface(self.surface)

    def setText(self, text):
        SDL_DestroyTexture(self.texture)
        SDL_FreeSurface(self.surface)
        if text == '':
            text = ' '
        self.surface = TTF_RenderUTF8_Blended(self.font.font, text.encode(), self.color)
        self.texture = SDL_CreateTextureFromSurface(self.renderer, self.surface)
        self.w = self.surface.contents.w
        self.h = self.surface.contents.h

    def draw(self, renderer):
        rect = SDL_Rect(round(self.x), round(self.y),
                round(self.scale * self.w), round(self.scale * self.h))
        if self.centered:
            rect.x -= round(rect.w / 2)
            rect.y -= round(rect.h / 2)
        SDL_RenderCopyEx(renderer, self.texture,
            None, rect, self.rotation, None, SDL_FLIP_NONE)


class UI:

    def __init__(self, renderer, next, textures, fonts):
        self.renderer = renderer
        self.next = next
        self.textures = {}
        self.fonts = {}
        self.sprites = []
        self.labels = []

        for name in textures:
            self.textures[name] = Texture(renderer, 'res/' + name)
        for font in fonts:
            self.fonts[font] = Font('res/' + font[0], font[1])

    def update(self):
        return self

    def onEvent(self, event):
        if event.type == SDL_WINDOWEVENT and \
            event.window.event == SDL_WINDOWEVENT_CLOSE:
            return None
        if event.type == SDL_KEYUP and event.key.keysym.sym == SDLK_ESCAPE:
            return self.next
        return self

    def draw(self, renderer):
        for sprite in self.sprites:
            sprite.draw(self.renderer)
        for label in self.labels:
            label.draw(self.renderer)


class SplashScreenUI(UI):

    def __init__(self, renderer, next):
        UI.__init__(self, renderer, next, ['splash.png', 'splash_logo.png'], [])

        self.sprites = [
            Sprite(self.textures['splash.png'], 0, 0),
            Sprite(self.textures['splash_logo.png'], 370, -180)
        ]
        self.start = time.time()

        self.beep = Mix_LoadWAV(b'res/beep.wav')
        self.beep_started = False

    def update(self):
        offset = time.time() - self.start
        if offset > 2:
            offset = 2
        offset = 225 * offset
        self.sprites[1].y = offset - 180

        if time.time() - self.start > 2 and not self.beep_started:
            Mix_PlayChannel(-1, self.beep, 0)
            self.beep_started = True
        if time.time() - self.start > 3:
            return self.next
        return UI.update(self)


class ConnectionUI(UI):

    def __init__(self, renderer):
        UI.__init__(self, renderer, None,
            ['menu.png', 'banner.png'],
            [('Comic Book.otf', 28),
            ('Comic Book.otf', 36),
            ('Comic Book Bold.otf', 42)])
        self.server = list(client.server)
        self.line = 0

        self.sprites = [
            Sprite(self.textures['menu.png'], 0, 0)
        ]

        self.labels = [
            Label(renderer, self.fonts[('Comic Book Bold.otf', 42)],
                'Connect to server', 640, 320,
                    color=SDL_Color(255, 255, 255), centered=True),
            Label(renderer, self.fonts[('Comic Book.otf', 36)],
                'Host name:', 640, 380,
                    color=SDL_Color(255, 255, 255), centered=True),
            Label(renderer, self.fonts[('Comic Book.otf', 36)],
                'Port number:', 640, 480,
                    color=SDL_Color(255, 255, 255), centered=True)
        ]

        self.server_labels = [
            Label(renderer, self.fonts[('Comic Book.otf', 28)],
                self.server[0] + '_', 640, 420,
                    color=SDL_Color(255, 255, 255), centered=True),
            Label(renderer, self.fonts[('Comic Book.otf', 28)],
                self.server[1], 640, 520,
                    color=SDL_Color(255, 255, 255), centered= True)
        ]

        self.labels += self.server_labels

        self.error = None
        self.error_bg = Sprite(self.textures['banner.png'], 0, 296)
        self.error_label = None

        self.music = Mix_LoadWAV(b'res/menu.wav')
        self.music_started = False

    def __del__(self):
        if self.music_started:
            Mix_HaltChannel(self.music_channel)

    def update(self):
        if not self.music_started:
            self.music_channel = Mix_PlayChannel(-1, self.music, -1)
            self.music_started = True
        return UI.update(self)

    def onEvent(self, event):
        if self.error and event.type == SDL_KEYUP:
            self.error_label = None
            self.error = None
            return self
        if event.type == SDL_TEXTINPUT:
            self.server[self.line] += event.text.text.decode()
            self.server_labels[self.line].setText(self.server[self.line] + '_')
            return self
        if event.type == SDL_KEYDOWN:
            if event.key.keysym.sym == SDLK_BACKSPACE:
                self.server[self.line] = self.server[self.line][:-1]
                self.server_labels[self.line].setText(self.server[self.line] + '_')
            return self
        if event.type == SDL_KEYUP:
            self.server_labels[self.line].setText(self.server[self.line])
            if event.key.keysym.sym == SDLK_TAB:
                self.line = (self.line + 1) % 2
                self.server_labels[self.line].setText(self.server[self.line] + '_')
                return self
            if event.key.keysym.sym == SDLK_UP:
                self.line = (self.line - 1) % 2
                self.server_labels[self.line].setText(self.server[self.line] + '_')
                return self
            if event.key.keysym.sym == SDLK_DOWN:
                self.line = (self.line + 1) % 2
                self.server_labels[self.line].setText(self.server[self.line] + '_')
                return self
            if event.key.keysym.sym == SDLK_RETURN:
                client.setServer(self.server)
                try:
                    return GameUI(self.renderer)
                except Exception as ex:
                    self.error = str(ex)
                return self

        return UI.onEvent(self, event)

    def draw(self, renderer):
        UI.draw(self, renderer)

        if self.error:
            if not self.error_label:
                self.error_label = Label(renderer, self.fonts[('Comic Book Bold.otf', 42)],
                    self.error, 640, 360, color=SDL_Color(200, 0, 0), centered=True)
            self.error_bg.draw(renderer)
            self.error_label.draw(renderer)


class GameUI(UI):

    def __init__(self, renderer):
        UI.__init__(self, renderer, ConnectionUI(renderer), [
                'grass.png',
                'banner.png',

                'egg.png',
                'egg_hatched.png',

                'items/food.png',
                'items/linemate.png',
                'items/deraumere.png',
                'items/sibur.png',
                'items/mendiane.png',
                'items/phiras.png',
                'items/thystame.png',

                'player_1/up1.png', 'player_1/up2.png',
                'player_1/right1.png', 'player_1/right2.png', 'player_1/right3.png',
                'player_1/down1.png', 'player_1/down2.png', 'player_1/down3.png',
                'player_1/left1.png', 'player_1/left2.png', 'player_1/left3.png',
                'player_1/incantation1.png', 'player_1/incantation2.png', 'player_1/incantation3.png', 'player_1/incantation4.png',
                'player_1/broadcast1.png', 'player_1/broadcast2.png',

                'player_2/up1.png', 'player_2/up2.png', 'player_2/up3.png',
                'player_2/right1.png', 'player_2/right2.png', 'player_2/right3.png',
                'player_2/down1.png', 'player_2/down2.png', 'player_2/down3.png',
                'player_2/left1.png', 'player_2/left2.png', 'player_2/left3.png',
                'player_2/incantation1.png', 'player_2/incantation2.png', 'player_2/incantation3.png', 'player_2/incantation4.png',
                'player_2/broadcast1.png', 'player_2/broadcast2.png',

                'player_3/up1.png', 'player_3/up2.png',
                'player_3/right1.png', 'player_3/right2.png',
                'player_3/down1.png', 'player_3/down2.png',
                'player_3/left1.png', 'player_3/left2.png',
                'player_3/incantation1.png', 'player_3/incantation2.png', 'player_3/incantation3.png', 'player_3/incantation4.png',
                'player_3/broadcast1.png', 'player_3/broadcast2.png',

                'player_4/up1.png', 'player_4/up2.png', 'player_4/up3.png',
                'player_4/right1.png', 'player_4/right2.png', 'player_4/right3.png',
                'player_4/down1.png', 'player_4/down2.png', 'player_4/down3.png',
                'player_4/left1.png', 'player_4/left2.png', 'player_4/left3.png',
                'player_4/incantation1.png', 'player_4/incantation2.png',
                'player_4/broadcast1.png', 'player_4/broadcast2.png'
            ], [
                ('Comic Book Bold.otf', 42)
        ])

        self.x_off = 0
        self.y_off = 0
        self.zoom = 1.0

        self.anim_counter = 0

        self.banner_bg = Sprite(self.textures['banner.png'], 0, 296)
        self.banner_label = None

        self.music = Mix_LoadWAV(b'res/music.wav')
        self.music_started = False

        self.cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND)

    def __del__(self):
        client.disconnect()
        if self.music_started:
            Mix_HaltChannel(self.music_channel)
        SDL_FreeCursor(self.cursor)

    def update(self):
        if not client.connected and not client.win_team:
            try:
                client.connect()
            except Exception as ex:
                self.next.error = str(ex)
                return self.next

        if not self.music_started:
            self.music_channel = Mix_PlayChannel(-1, self.music, -1)
            self.music_started = True

        SDL_SetCursor(self.cursor)

        self.anim_counter += 1
        self.sprites = []

        self.makeMapSprites()
        self.makePlayerSprites()
        self.makeEggSprites()

        return UI.update(self)

    def onEvent(self, event):
        if event.type == SDL_MOUSEWHEEL:
            self.zoom += event.wheel.y * 0.05
            if self.zoom < 0.01:
                self.zoom = 0.01
            return self
        if event.type == SDL_MOUSEMOTION and event.motion.state & SDL_BUTTON_LMASK:
            self.x_off += event.motion.xrel
            self.y_off += event.motion.yrel
            return self
        if event.type == SDL_KEYDOWN:
            if event.key.keysym.sym == SDLK_PAGEUP:
                client.socket.send(b'sst %d' % (client.freq + 1))
                return self
            if event.key.keysym.sym == SDLK_PAGEDOWN and client.freq > 1:
                client.socket.send(b'sst %d' % (client.freq - 1))
                return self

        return UI.onEvent(self, event)

    def draw(self, renderer):
        if client.win_team:
            if not self.banner_label:
                self.banner_label = Label(renderer,
                    self.fonts[('Comic Book Bold.otf', 42)],
                    'Team ' + client.win_team.name + ' won', 640, 360, centered=True)
            self.banner_bg.draw(renderer)
            self.banner_label.draw(renderer)
        UI.draw(self, renderer)

    def makeMapSprites(self):
        itemTextures = [self.textures[name] for name in [
            'items/food.png',
            'items/linemate.png',
            'items/deraumere.png',
            'items/sibur.png',
            'items/mendiane.png',
            'items/phiras.png',
            'items/thystame.png'
        ]]

        for x in range(client.map.w):
            for y in range(client.map.h):
                self.sprites.append(Sprite(self.textures['grass.png'],
                    *self.mapCoordinates(x, y), scale=self.zoom))
                content = client.map.tiles[x][y]
                random.seed(x + y * client.map.w)
                for i,c in enumerate(content):
                    for j in range(c):
                        coord = list(self.mapCoordinates(x, y))
                        coord[0] = coord[0] + random.random() * 40 * self.zoom
                        coord[1] = coord[1] + random.random() * 40 * self.zoom
                        self.sprites.append(Sprite(itemTextures[i],
                            *coord, scale=0.5*self.zoom))

    def makePlayerSprites(self):
        teamAnimsSeeds = [
            [2, 3, 3, 3, 4, 2],
            [3, 3, 3, 3, 4, 2],
            [2, 2, 2, 2, 4, 2],
            [3, 3, 3, 3, 2, 2]
        ]
        teamAnims = []
        for i,seed in enumerate(teamAnimsSeeds):
            folder = 'player_%d/' % (i + 1)
            teamAnim = {}
            for j,anim in enumerate(['up', 'right', 'down', 'left', 'incantation', 'broadcast']):
                teamAnim[anim] = [folder + anim + str(k + 1) + '.png' for k in range(seed[j])]
            teamAnims.append(teamAnim)

        for i,team in enumerate(client.map.teams):
            playerAnims = {}
            for anim in teamAnims[i % 4]:
                playerAnims[anim] = [self.textures[name] for name in teamAnims[i % 4][anim]]
            for player in team.players:
                if player.broadcast:
                    anim = playerAnims['broadcast']
                    player.broadcast_timer -= 1
                    if player.broadcast_timer <= 0:
                        player.broadcast = None
                elif player.incantation:
                    anim = playerAnims['incantation']
                else:
                    anim = playerAnims[['up','right','down','left'][player.orientation - 1]]
                self.sprites.append(Sprite(anim[int(self.anim_counter / 10 % len(anim))],
                    *self.mapCoordinates(player.x, player.y), scale=2.0 * self.zoom))

    def makeEggSprites(self):
        for egg in client.map.eggs:
            texture = 'egg.png'
            if egg.hatched:
                texture = 'egg_hatched.png'
            self.sprites.append(Sprite(self.textures[texture],
                *[c+8 for c in self.mapCoordinates(egg.x, egg.y)], scale=1.0 * self.zoom))

    def mapCoordinates(self, x, y):
        y = client.map.h - y - 1
        return (self.x_off + x * 64 * self.zoom, self.y_off + y * 64 * self.zoom)


class ZappyGUI:
    def __init__(self, server=None):
        self.server = server

    def run(self):
        if SDL_Init(SDL_INIT_AUDIO |SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0:
            print('Failed to init SDL: %s' % SDL_GetError().decode(),
                file=sys.stderr)
            return 84
        if IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG:
            print('Failed to init SDL_image: %s' % IMG_GetError().decode(),
                file=sys.stderr)
            return 84
        if TTF_Init() != 0:
            print('Failed to init SDL_ttf: %s' % TTF_GetError().decode(),
                file=sys.stderr)
            return 84
        if Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0:
            print('Failed to init SDL_mixer: %s' % Mix_GetError().decode(),
                file=sys.stderr)
            return 84

        global client
        client = Client()
        if self.server:
            client.setServer(self.server)

        window = SDL_CreateWindow("Zappy GUI".encode(),
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWEVENT, 1280, 720, 0)
        icon = Surface('res/egg_hatched.png')
        SDL_SetWindowIcon(window, icon.surface)
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC)

        current_ui = SplashScreenUI(renderer,
            GameUI(renderer) if self.server else ConnectionUI(renderer))
        event = SDL_Event()

        while current_ui:
            next_ui = current_ui.update()
            if next_ui != current_ui:
                del current_ui
                current_ui = next_ui

            while current_ui and SDL_PollEvent(event) != 0:
                next_ui = current_ui.onEvent(event)

                if next_ui != current_ui:
                    del current_ui
                    current_ui = next_ui

            if current_ui:
                SDL_RenderClear(renderer)
                current_ui.draw(renderer)
                SDL_RenderPresent(renderer)

        SDL_DestroyRenderer(renderer)
        SDL_DestroyWindow(window)
        del icon

        Mix_CloseAudio()
        TTF_Quit()
        IMG_Quit()
        SDL_Quit()

        return 0
