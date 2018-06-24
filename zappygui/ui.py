import sys
import time

from sdl2 import *
from sdl2.sdlimage import *
from sdl2.sdlttf import *

class UI:

    def __init__(self, next):
        self.next = next

    def update(self, event):
        return self

    def draw(self):
        return self


class SplashScreenUI(UI):

    def __init__(self, next):
        UI.__init__(self, next)

        self.start = time.time()

    def update(self, event):
        UI.update(self, event)
        return self

    def draw(self):
        UI.draw(self)

        if time.time() - self.start > 2:
            return self.next
        else:
            return self

class ConnectionUI(UI):

        def __init__(self):
            UI.__init__(self, None)

        def update(self, event):
            return self

class ZappyGUI:
    def __init__(self, server=None):
        self.server = server

    def run(self):
        if SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0:
            print('Failed to init SDL2: %s' % SDL_GetError().decode(), file=sys.stderr)
            return 84
        if IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG:
            print('Failed to init SDL_image: %s' % IMG_GetError().decode())
            return 84
        if TTF_Init() != 0:
            print('Failed to init SDL_ttf: %s' % TTF_GetError().decode())
            return 84

        current_ui = SplashScreenUI(ConnectionUI())
        event = SDL_Event()

        while current_ui:
            current_ui.draw()

            while current_ui and SDL_PollEvent(event) != 0:
                old_ui = current_ui

                if event.type == SDL_WINDOWEVENT and event.window.event == SDL_WINDOWEVENT_CLOSE:
                    current_ui = None
                if event.type == SDL_KEYUP and event.key.keysym.sym == SDLK_ESCAPE:
                    current_ui = current_ui.next
                else:
                    current_ui = current_ui.update(event)

                if current_ui != old_ui:
                    del old_ui

        TTF_Quit()
        IMG_Quit()
        SDL_Quit()

        return 0
