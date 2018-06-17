/*
** EPITECH PROJECT, 2018
** aled_list
** File description:
** output a list into a file
*/

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "aled_list.h"

int aled_list_to_file(aled_list_t *list, char *path, int options)
{
	aled_list_link_t *pnt;
	int mode;
	int fd;

	mode = ((options & ALED_LIST_APPEND) ? O_APPEND : O_TRUNC);
	if ((fd = open(path, O_WRONLY | mode)) < 0)
		return (EXIT_FAILURE);
	pnt = list->head;
	while (pnt != NULL) {
		write(fd, pnt->data, strlen(pnt->data));
		write(fd, "\n", 1);
		pnt = pnt->next;
	}
	close(fd);
	return (EXIT_SUCCESS);
}
