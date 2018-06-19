/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Circular buffers abstraction (IO routines)
*/

#include <assert.h>
#include <string.h>

#include "cbuf.h"

size_t cbuf_read(cbuf_t *cb, void *buf, size_t n)
{
	if (buf)
		n = cbuf_peek(cb, buf, n);
	cb->tail = (cb->tail + n) % (cb->size + 1);
	return (n);
}

size_t cbuf_peek(cbuf_t *cb, void *buf, size_t n)
{
	size_t rdsz = 0;
	size_t sz;
	size_t tail = cb->tail;

	n = min(n, cbuf_used_bytes(cb));
	while (rdsz < n) {
		sz = min(cb->size - tail + 1, n - rdsz);
		memcpy(buf + rdsz, cb->buf + tail, sz);
		tail = (tail + sz) % (cb->size + 1);
		rdsz += sz;
	}
	return (rdsz);
}

size_t cbuf_write(cbuf_t *cb, void const *buf, size_t n)
{
	size_t wrsz = 0;
	size_t sz;

	n = min(n, cbuf_free_bytes(cb));
	while (wrsz < n) {
		sz = min(cb->size - cb->head + 1, n - wrsz);
		memcpy(cb->buf + cb->head, buf + wrsz, sz);
		cb->head = (cb->head + sz) % (cb->size + 1);
		wrsz += sz;
	}
	return (wrsz);
}
