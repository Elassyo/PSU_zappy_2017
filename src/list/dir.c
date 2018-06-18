/*
** EPITECH PROJECT, 2018
** aled_list
** File description:
** get a list of files from a directory
*/

#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "aled_list.h"

aled_list_t *aled_list_dir(char *path, int options)
{
	aled_list_t *list;
	struct dirent **dir;
	int nb;

	if ((list = aled_list_create()) == NULL)
		return (NULL);
	if ((nb = scandir(path, &dir, NULL, alphasort)) == -1)
		return (NULL);
	while (nb--) {
		if (dir[nb]->d_name[0] != '.'
			|| !(options & ALED_LIST_NO_DOTFILES))
			if (!(aled_list_push(list, strdup(dir[nb]->d_name))))
				return (NULL);
		free(dir[nb]);
	}
	free(dir);
	return (list);
}
