/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Circular buffers abstraction
*/

#include <stdlib.h>

#include "cbuf.h"

bool cbuf_create(cbuf_t *cb, size_t sz)
{
	cb->buf = malloc(sz + 1);
	if (cb->buf == NULL)
		return (false);
	cb->size = sz;
	cb->head = 0;
	cb->tail = 0;
	return (true);
}

void cbuf_destroy(cbuf_t *cb)
{
	free(cb->buf);
	cb->buf = NULL;
	cb->size = 0;
}

size_t cbuf_free_bytes(cbuf_t const *cb)
{
	if (cb->head >= cb->tail)
		return (cb->size - cb->head + cb->tail);
	else
		return (cb->tail - cb->head - 1);
}

size_t cbuf_used_bytes(cbuf_t const *cb)
{
	return (cb->size - cbuf_free_bytes(cb));
}
