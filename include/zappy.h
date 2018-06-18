/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Zappy common header
*/

#if !defined (ZAPPY_H_)
	#define ZAPPY_H_

	#define ZPY_GRAPHICAL_TEAM "GRAPHICAL"

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

#endif /* !defined (ZAPPY_H_) */
