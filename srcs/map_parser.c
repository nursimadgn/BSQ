/*
** EPITECH PROJECT, 2026
** bsq
** File description:
** Map parsing and memory management helpers
**/

#include "bsq.h"

int	read_line(int fd, char *line, int size)
{
	int		i;
	char	c;

	i = 0;
	while (i < size - 1)
	{
		if (read(fd, &c, 1) <= 0)
			return (0);
		if (c == '\n')
			break ;
		line[i++] = c;
	}
	line[i] = '\0';
	return (1);
}

int	fill_row(int fd, t_map *map, int index)
{
	char	line[1000];
	int		len;
	int		j;

	if (!read_line(fd, line, sizeof(line)))
		return (0);
	len = ft_strlen(line);
	if (index == 0)
		map->cols = len;
	else if (len != map->cols)
		return (0);
	map->grid[index] = malloc(map->cols + 1);
	if (!map->grid[index])
		return (0);
	j = 0;
	while (j < len)
	{
		if (line[j] != map->empty && line[j] != map->obstacle)
			return (0);
		map->grid[index][j] = line[j];
		j++;
	}
	map->grid[index][j] = '\0';
	return (1);
}

int	fill_grid(int fd, t_map *map)
{
	int	i;

	map->grid = malloc(sizeof(char *) * map->rows);
	if (!map->grid)
		return (0);
	i = 0;
	while (i < map->rows)
	{
		if (!fill_row(fd, map, i))
			return (0);
		i++;
	}
	return (1);
}

int	parse_header(int fd, t_map *map)
{
	char	buf[100];
	int		i;

	i = 0;
	while (read(fd, &buf[i], 1) && buf[i] != '\n' && i < 99)
		i++;
	buf[i] = '\0';
	if (i < 4)
		return (0);
	map->full = buf[--i];
	map->obstacle = buf[--i];
	map->empty = buf[--i];
	buf[i] = '\0';
	map->rows = ft_atoi(buf);
	return (map->rows > 0 && map->empty != map->obstacle
		&& map->empty != map->full && map->obstacle != map->full);
}

t_map	*parse_map(char *filepath)
{
	int		fd;
	t_map	*map;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (!map || !parse_header(fd, map))
	{
		close(fd);
		free(map);
		return (NULL);
	}
	if (!fill_grid(fd, map))
	{
		close(fd);
		free_map(map);
		return (NULL);
	}
	close(fd);
	return (map);
}
