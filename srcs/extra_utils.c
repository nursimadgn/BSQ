/*
** EPITECH PROJECT, 2026
** bsq
** File description:
** Additional utility helpers
*/

#include "bsq.h"

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

int	ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;

    while (s1[i] != '\0' && s2[i] != '\0' )
    {
        if(s1[i] == s2[i])
        {
            i++;
        }
        else
        {
             return(s1[i]- s2[i]);
        }
        

    }
    return(s1[i]- s2[i]);
	
}

int read_loop(int fd, char *line, int size, int *ret)
{
    int     i;
    char    c;

    i = 0;
    *ret = 1;
    while (i < size - 1)
    {
        *ret = read(fd, &c, 1);
        if (*ret <= 0)
            break ;
        if (c == '\r')
            continue ;
        if (c == '\n')
            break ;
        line[i++] = c;
    }
    return (i);
}

void flush_line(int fd)
{
    char c;

    while (read(fd, &c, 1) > 0 && c != '\n')
        ;
}

int validate_row(char *line, t_map *map, int index)// komediyiz dimi abi makarayz dimi abi
{
    int j;

    j = 0;
    while (j < map->cols)
    {
        if (line[j] != map->empty && line[j] != map->obstacle)
            return (0);
        map->grid[index][j] = line[j];
        j++;
    }
    map->grid[index][j] = '\0';
    return (1);
}