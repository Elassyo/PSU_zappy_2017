/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Zappy common header
*/

#if !defined (ZAPPY_H_)
	#define ZAPPY_H_

	#define U(x) (unsigned int)(x)

	#define ZPY_GRAPHIC_TEAM "GRAPHIC"

typedef enum zpy_direction {
	UP,
	RIGHT,
	DOWN,
	LEFT,
	NDIRECTIONS
} zpy_direction_t;

typedef enum zpy_item_type {
	FOOD,
	LINEMATE,
	DERAUMERE,
	SIBUR,
	MENDIANE,
	PHIRAS,
	THYSTAME,
	NITEM_TYPES
} zpy_item_type_t;

typedef struct zpy_ritual {
	unsigned int nb_players;
	unsigned char items[NITEM_TYPES];
} zpy_ritual_t;

#endif /* !defined (ZAPPY_H_) */
