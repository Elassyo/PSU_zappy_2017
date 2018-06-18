/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Zappy server header
*/

#if !defined (ZAPPY_SERVER_H_)
	#define ZAPPY_SERVER_H_

	#include "tcp.h"
	#include "list.h"
	#include "zappy.h"

typedef struct zpy_srv_player {
	unsigned short team;
	unsigned int x;
	unsigned int y;
	zpy_direction_t direction;
	unsigned char level;
	unsigned char inventory[NITEM_TYPES];
	unsigned short food_amount;
	unsigned int food_countdown;
	unsigned int action_countdown;
} zpy_srv_player_t;

typedef struct zpy_srv_item_group {
	unsigned int x;
	unsigned int y;
	unsigned short amount;
	zpy_item_type_t type;
} zpy_srv_item_group_t;

typedef struct zpy_srv_map {
	unsigned int width;
	unsigned int height;
	list_t *players; /* list_t<zpy_srv_player_t*> */
	list_t *items; /* list_t<zpy_srv_item_group_t*> */
} zpy_srv_map_t;

typedef struct zpy_srv {
	tcp_server_t tcp;
	uint16_t port;
	zpy_srv_map_t map;
	unsigned int max_clients;
	unsigned int freq;
	list_t *teamnames; /* list_t<char const*> */
} zpy_srv_t;

typedef enum zpy_srv_client_type {
	UNKNOWN,
	GRAPHIC,
	IA
} zpy_srv_client_type_t;

typedef struct zpy_srv_client {
	zpy_srv_t *server;
	zpy_srv_client_type_t type;
	zpy_srv_player_t *player;
} zpy_srv_client_t;

typedef struct zpy_srv_cmd {
	char const *str;
	bool (*handler)(tcp_conn_t*, zpy_srv_client_t*, char const*);
	unsigned int completion_time;
} zpy_srv_cmd_t;

bool zpy_srv_args_parse(zpy_srv_t *server, int ac, char **av);

bool zpy_srv_map_init(zpy_srv_map_t *map);
void zpy_srv_map_cleanup(zpy_srv_map_t *map);

zpy_srv_player_t *zpy_srv_player_new(zpy_srv_map_t *map, unsigned short team);

void zpy_srv_player_move_forward(zpy_srv_map_t *map, zpy_srv_player_t *player);
void zpy_srv_player_turn_left(zpy_srv_player_t *player);
void zpy_srv_player_turn_right(zpy_srv_player_t *player);

bool zpy_srv_player_item_take(zpy_srv_map_t *map, zpy_srv_player_t *player,
	zpy_item_type_t item_type);
bool zpy_srv_player_item_drop(zpy_srv_map_t *map, zpy_srv_player_t *player,
	zpy_item_type_t item_type);

void zpy_srv_conn_on_connect(tcp_conn_t *conn, void *args);
void zpy_srv_conn_on_disconnect(tcp_conn_t *conn);
bool zpy_srv_conn_on_data(tcp_conn_t *conn);

bool zpy_srv_dispatch_cmd(tcp_conn_t *conn,
	char const *cmd, char const *args);

bool cmd_forward(tcp_server_conn_t *conn, zpy_srv_client_t *cmd,
		char const *args);
bool cmd_left(tcp_server_conn_t *conn, zpy_srv_client_t *cmd,
		char const *args);
bool cmd_right(tcp_server_conn_t *conn, zpy_srv_client_t *cmd,
		char const *args);
bool cmd_look(tcp_server_conn_t *conn, zpy_srv_client_t *cmd,
		char const *args);
bool cmd_inventory(tcp_server_conn_t *conn, zpy_srv_client_t *cmd,
		char const *args);
bool cmd_broadcast(tcp_server_conn_t *conn, zpy_srv_client_t *cmd,
		char const *args);
bool cmd_connect(tcp_server_conn_t *conn, zpy_srv_client_t *cmd,
		char const *args);
bool cmd_fork(tcp_server_conn_t *conn, zpy_srv_client_t *cmd,
		char const *args);
bool cmd_eject(tcp_server_conn_t *conn, zpy_srv_client_t *cmd,
		char const *args);
bool cmd_take(tcp_server_conn_t *conn, zpy_srv_client_t *cmd,
		char const *args);
bool cmd_set(tcp_server_conn_t *conn, zpy_srv_client_t *cmd,
		char const *args);
bool cmd_incantation(tcp_server_conn_t *conn, zpy_srv_client_t *cmd,
		char const *args);

#endif /* !defined (ZAPPY_SERVER_H_) */
