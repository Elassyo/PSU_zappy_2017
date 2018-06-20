/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Circular buffers abstraction
*/

#if !defined (CBUF_H_)
	#define CBUF_H_

	#include <stdbool.h>
	#include <stddef.h>

	#ifdef __cplusplus
extern "C" {
	#endif

typedef struct cbuf {
	void *buf;
	size_t size;
	size_t head;
	size_t tail;
} cbuf_t;

bool cbuf_create(cbuf_t *cb, size_t sz);
void cbuf_destroy(cbuf_t *cb);

size_t cbuf_free_bytes(cbuf_t const *cb);
size_t cbuf_used_bytes(cbuf_t const *cb);

size_t cbuf_read(cbuf_t *cb, void *buf, size_t n);
size_t cbuf_peek(cbuf_t *cb, void *buf, size_t n);
size_t cbuf_write(cbuf_t *cb, void const *buf, size_t n);

inline __attribute__ ((always_inline)) size_t min(size_t a, size_t b)
{
	return (a < b ? a : b);
}

	#ifdef __cplusplus
}
	#endif

#endif /* !defined (CBUF_H_) */
