/*
** EPITECH PROJECT, 2026
** bsq
** File description:
** Additional utility helpers
*/

#include "bsq.h"

int	ft_is_empty(char c)
{
	return (c == '.');
}

int	ft_is_obstacle(char c)
{
	return (c == 'o');
}

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->grid)
	{
		i = 0;
		while (i < map->rows)
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	free(map);
}
