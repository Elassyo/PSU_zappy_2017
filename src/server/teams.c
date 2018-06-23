/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Teams routines
*/

#include <string.h>

#include "zappy_server.h"

bool zpy_srv_teams_init(zpy_srv_t *server)
{
	list_node_t *node;
	zpy_srv_team_t *team;

	node = server->teams->head;
	while (node != NULL) {
		team = node->data;
		team->max_players = server->max_players;
		team->players = list_create(true);
		if (team->players == NULL)
			return (false);
		node = node->next;
	}
	return (true);
}

void zpy_srv_teams_cleanup(list_t *teams)
{
	list_node_t *node;
	zpy_srv_team_t *team;

	node = teams->head;
	while (node != NULL) {
		team = node->data;
		list_destroy(team->players);
		node = node->next;
	}
}

static bool zpy_srv_team_join(tcp_conn_t *conn, zpy_srv_client_t *client,
	unsigned short i)
{
	zpy_srv_team_t *team;
	int x = -1;
	int y = -1;

	team = list_get(client->server->teams, i);
	if (team->players->len == team->max_players) {
		tcp_conn_printf(conn, "ko\n");
		return (true);
	}
	if (team->players->len > client->server->max_players &&
		!zpy_srv_egg_use_hatched(client->server, i, &x, &y))
		return (false);
	zpy_srv_map_add_food(client->server);
	client->type = CLIENT_AI;
	zpy_srv_player_new(client, i, x, y);
	client->player->conn = conn;
	tcp_conn_printf(conn, "%d\n", team->max_players - team->players->len);
	tcp_conn_printf(conn, "%u %u\n",
		client->server->map.width, client->server->map.height);
	return (true);
}

bool zpy_srv_teams_join(tcp_conn_t *conn, zpy_srv_client_t *client,
	char const *name)
{
	unsigned short i = 0;
	list_node_t *node;
	zpy_srv_team_t *team;

	if (strcmp(name, ZPY_GRAPHIC_TEAM) == 0) {
		client->type = CLIENT_GRAPHIC;
		return (zpy_srv_grph_add(client->server, conn));
	}
	node = client->server->teams->head;
	while (node != NULL) {
		team = node->data;
		if (strcmp(team->name, name) == 0)
			return (zpy_srv_team_join(conn, client, i));
		node = node->next;
		i++;
	}
	tcp_conn_printf(conn, "ko\n");
	return (true);
}
