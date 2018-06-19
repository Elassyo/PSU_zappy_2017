/*
** EPITECH PROJECT, 2018
** cmd map
** File description:
** cmd map
*/

#include <stdio.h>
#include <string.h>
#include "zappy_server.h"

bool cmd_msz(tcp_conn_t *conn,
		zpy_srv_client_t *client,
		__attribute__((unused))char const *cmd)
{
	char buff[256];

	snprintf(buff, 256, "msz %u %u\n", client->server->map.width,
		client->server->map.height);
	cbuf_write(&conn->out, &buff, strlen(buff));
	return (true);
}

bool cmd_bct(tcp_conn_t *conn,
		zpy_srv_client_t *client,
		char const *cmd)
{
	/* int x = -1; */
	/* int y = -1; */
	/* char count[7]; */
	/* zpy_srv_item_group_t *obj; */

	/* memset(count, 0, 7); */
	/* sscanf(cmd, "%d %d", &x, &y); */
	/* if (x == -1 || y == -1) { */
	/* 	cbuf_write(&conn->out, "ko\n", 3); */
	/* 	return (true); */
	/* } */
	/* for (list_node_t *curr = client->server->map.items->head; curr != NULL; curr = curr->next) { */
	/* 	obj = (zpy_srv_item_group_t *)curr->data; */
	/* 	printf("%u %u\n", obj->x, obj->y); */
	/* } */
	/* /\* printf("%s et %d %d\n", cmd, x, y); *\/ */
	/* cbuf_write(&conn->out, cmd, strlen(cmd)); */
	return (true);
}
