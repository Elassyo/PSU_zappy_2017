/*
** EPITECH PROJECT, 2018
** aled_list
** File description:
** lib header
*/

#ifndef ALED_LIST_H_
	#define ALED_LIST_H_

	#include <stdlib.h>

	#ifndef EXIT_SUCCESS
		#define EXIT_SUCCESS	0
	#endif /* !EXIT_SUCCESS */
	#ifndef EXIT_FAILURE
		#define EXIT_FAILURE	1
	#endif /* !EXIT_FAILURE */

/*
**	OPTIONS BITMASK
*/
	#define ALED_LIST_NO_DOTFILES	1
	#define ALED_LIST_APPEND	2


/*
**	LISTS
*/
typedef struct aled_list_link_s {
	void *data;
	struct aled_list_link_s *next;
	struct aled_list_link_s *prev;
} aled_list_link_t;

typedef struct aled_list_s {
	aled_list_link_t *head;
	aled_list_link_t *back;
	unsigned int len;
} aled_list_t;

aled_list_t	*aled_list_create(void);
int		aled_list_push(aled_list_t *, void *data);
void		aled_list_pop(aled_list_t *);
int		aled_list_push_back(aled_list_t *, void *data);
void		aled_list_pop_back(aled_list_t *);
int		aled_list_add(aled_list_t *, unsigned int index, void *data);
int		aled_list_remove(aled_list_t *, unsigned int index);
void		aled_list_destroy(aled_list_t *);
void		*aled_list_get(aled_list_t *, unsigned int index);
aled_list_t	*aled_list_dir(char *path, int options);
void		aled_list_print_strs(aled_list_t *list, char *format);
int		aled_list_to_file(aled_list_t *, char *path, int options);

#endif /* !ALED_LIST_H_ */
