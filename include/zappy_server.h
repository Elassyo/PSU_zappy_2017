/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Zappy server header
*/

#if !defined (ZAPPY_SERVER_H_)
	#define ZAPPY_SERVER_H_

	#include <time.h>

	#include "tcp.h"
	#include "list.h"
	#include "zappy.h"

typedef enum zpy_srv_client_type zpy_srv_client_type_t;

typedef struct zpy_srv zpy_srv_t;
typedef struct zpy_srv_cmd zpy_srv_cmd_t;
typedef struct zpy_srv_team zpy_srv_team_t;
typedef struct zpy_srv_client zpy_srv_client_t;
typedef struct zpy_srv_map zpy_srv_map_t;
typedef struct zpy_srv_item_group zpy_srv_item_group_t;
typedef	struct zpy_srv_egg zpy_srv_egg_t;
typedef	struct zpy_srv_player zpy_srv_player_t;

enum zpy_srv_client_type {
	CLIENT_UNKNOWN,
	CLIENT_GRAPHIC,
	CLIENT_AI
};

struct zpy_srv_map {
	unsigned int width;
	unsigned int height;
	list_t *players; /* list_t<zpy_srv_player_t*> */
	list_t *items; /* list_t<zpy_srv_item_group_t*> */
};

struct zpy_srv {
	tcp_server_t tcp;
	uint16_t port;
	zpy_srv_map_t map;
	unsigned int max_players;
	unsigned int freq;
	list_t *teams; /* list_t<zpy_srv_team_t*> */
	list_t *graphic_clients; /* list_t<tcp_conn_t*> */
	struct timespec last_tick;
	unsigned int last_player_id;
	list_t *eggs; /* list_t<zpy_srv_egg_t*> */
};

struct zpy_srv_cmd {
	char const *str;
	bool (*handler)(tcp_conn_t*, zpy_srv_client_t*, char const*);
	zpy_srv_client_type_t client_type;
	unsigned int countdown;
	char *args;
};

struct zpy_srv_team {
	char const *name;
	unsigned int max_players;
	list_t *players;  /* list_t<zpy_srv_player_t*> */
};

struct zpy_srv_client {
	zpy_srv_t *server;
	zpy_srv_client_type_t type;
	zpy_srv_player_t *player;
	struct timespec last_tick;
};

struct zpy_srv_item_group {
	unsigned int x;
	unsigned int y;
	unsigned char amount;
	zpy_item_type_t type;
};

struct zpy_srv_egg {
	unsigned int id;
	unsigned int creator_id;
	unsigned int x;
	unsigned int y;
	unsigned int countdown;
	unsigned int team;
};

struct zpy_srv_player {
	unsigned int id;
	tcp_conn_t *conn;
	unsigned short team;
	unsigned int x;
	unsigned int y;
	zpy_direction_t direction;
	unsigned char level;
	unsigned char inventory[NITEM_TYPES];
	unsigned int food_countdown;
	list_t *cmd_queue; /* list_t<zpy_srv_cmd_t*> */
};

bool zpy_srv_args_parse(zpy_srv_t *server, int ac, char **av);

void zpy_srv_conn_on_connect(tcp_conn_t *conn, void *args);
void zpy_srv_conn_on_disconnect(tcp_conn_t *conn);
bool zpy_srv_conn_on_tick(tcp_conn_t *conn);

bool zpy_srv_teams_init(zpy_srv_t *server);
void zpy_srv_teams_cleanup(list_t *teams);
bool zpy_srv_teams_join(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *name);

bool zpy_srv_map_init(zpy_srv_t *server);
void zpy_srv_map_cleanup(zpy_srv_map_t *map);

zpy_srv_item_group_t *zpy_srv_map_find_item_group(zpy_srv_map_t *map,
	unsigned int x, unsigned int y, zpy_item_type_t item_type);
int zpy_srv_map_find_item_group_idx(zpy_srv_map_t *map,
	unsigned int x, unsigned int y, zpy_item_type_t item_type);
bool zpy_srv_map_add_item(zpy_srv_map_t *map,
	unsigned int x, unsigned int y, zpy_item_type_t item_type);

list_t *zpy_srv_map_players_on_tile(zpy_srv_map_t *map, size_t x, size_t y);

bool zpy_srv_player_new(zpy_srv_client_t *client, unsigned short team);
void zpy_srv_player_remove(zpy_srv_t *server, zpy_srv_player_t *player);

bool zpy_srv_player_tick(tcp_conn_t *conn, zpy_srv_player_t *player);

zpy_srv_player_t *zpy_srv_player_find(zpy_srv_map_t *map, unsigned int id);

void zpy_srv_player_move_forward(zpy_srv_map_t *map, zpy_srv_player_t *player);
void zpy_srv_player_turn_left(zpy_srv_player_t *player);
void zpy_srv_player_turn_right(zpy_srv_player_t *player);

bool zpy_srv_player_item_take(zpy_srv_map_t *map, zpy_srv_player_t *player,
	zpy_item_type_t item_type);
bool zpy_srv_player_item_drop(zpy_srv_map_t *map, zpy_srv_player_t *player,
	zpy_item_type_t item_type);

size_t zpy_srv_get_vision_tile_pos(zpy_srv_map_t *map,
	zpy_srv_player_t *player, size_t tile);

zpy_srv_egg_t *zpy_srv_egg_init(size_t *id, zpy_srv_player_t *parent);
void zpy_srv_tick_eggs(zpy_srv_t *server);

bool zpy_srv_grph_add(zpy_srv_t *server, tcp_conn_t *conn);
void zpy_srv_grph_remove(zpy_srv_t *server, tcp_conn_t *conn);

void zpy_srv_grph_send(tcp_conn_t *conn,
	void (*handler)(tcp_conn_t *, va_list), ...);
void zpy_srv_grph_sendall(zpy_srv_t *server,
	void (*handler)(tcp_conn_t *, va_list), ...);

bool zpy_srv_dispatch_cmd(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *cmd, char const *args);

bool zpy_srv_cmd_broadcast(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args);
bool zpy_srv_cmd_connect(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args);
bool zpy_srv_cmd_eject(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args);
bool zpy_srv_cmd_fork(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args);
bool zpy_srv_cmd_forward(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args);
bool zpy_srv_cmd_incantation(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args);
bool zpy_srv_cmd_inventory(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args);
bool zpy_srv_cmd_left(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args);
bool zpy_srv_cmd_look(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args);
bool zpy_srv_cmd_right(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args);
bool zpy_srv_cmd_set(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args);
bool zpy_srv_cmd_take(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args);

bool zpy_srv_cmd_msz(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args);
bool zpy_srv_cmd_bct(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args);
bool zpy_srv_cmd_mct(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args);
bool zpy_srv_cmd_pin(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args);
bool zpy_srv_cmd_plv(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args);
bool zpy_srv_cmd_ppo(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args);
bool zpy_srv_cmd_sgt(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args);
bool zpy_srv_cmd_sst(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args);
bool zpy_srv_cmd_tna(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *args);

/* args: unsigned int x, unsigned int y */
void zpy_srv_grph_bct(tcp_conn_t *conn, va_list args);
/* args: zpy_srv_egg_t *egg */
void zpy_srv_grph_ebo(tcp_conn_t *conn, va_list args);
/* args: zpy_srv_egg_t *egg */
void zpy_srv_grph_eht(tcp_conn_t *conn, va_list args);
/* args: zpy_srv_egg_t *egg */
void zpy_srv_grph_enw(tcp_conn_t *conn, va_list args);
/* args: none */
void zpy_srv_grph_mct(tcp_conn_t *conn, va_list args);
/* args: none */
void zpy_srv_grph_msz(tcp_conn_t *conn, va_list args);
/* args: zpy_srv_player_t *player, char const *msg */
void zpy_srv_grph_pbc(tcp_conn_t *conn, va_list args);
/* args: zpy_srv_player_t *player */
void zpy_srv_grph_pdi(tcp_conn_t *conn, va_list args);
/* args: zpy_srv_player_t *player, zpy_item_type_t type */
void zpy_srv_grph_pdr(tcp_conn_t *conn, va_list args);
/* args: zpy_srv_player_t *player */
void zpy_srv_grph_pex(tcp_conn_t *conn, va_list args);
/* args: zpy_srv_player_t *player */
void zpy_srv_grph_pfk(tcp_conn_t *conn, va_list args);
/* args: zpy_srv_player_t *player, zpy_item_type_t type */
void zpy_srv_grph_pgt(tcp_conn_t *conn, va_list args);
/* args: list_t<zpy_srv_player_t*> *players */
void zpy_srv_grph_pic(tcp_conn_t *conn, va_list args);
/* args: unsigned int x, unsigned int y, int success */
void zpy_srv_grph_pie(tcp_conn_t *conn, va_list args);
/* args: zpy_srv_player_t *player */
void zpy_srv_grph_pin(tcp_conn_t *conn, va_list args);
/* args: zpy_srv_player_t *player */
void zpy_srv_grph_plv(tcp_conn_t *conn, va_list args);
/* args: zpy_srv_player_t *player */
void zpy_srv_grph_pnw(tcp_conn_t *conn, va_list args);
/* args: zpy_srv_player_t *player */
void zpy_srv_grph_ppo(tcp_conn_t *conn, va_list args);
/* args: none */
void zpy_srv_grph_sgt(tcp_conn_t *conn, va_list args);
/* args: unsigned int freq */
void zpy_srv_grph_sst(tcp_conn_t *conn, va_list args);
/* args: none */
void zpy_srv_grph_tna(tcp_conn_t *conn, va_list args);

inline __attribute__ ((always_inline)) double timespec_diff(
	struct timespec const *a, struct timespec const *b)
{
	return ((a->tv_sec + (double)a->tv_nsec / 1000000000) -
		(b->tv_sec + (double)b->tv_nsec / 1000000000));
}

#endif /* !defined (ZAPPY_SERVER_H_) */
