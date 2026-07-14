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

int	store_row(int fd, t_map *map, int row_index)
{
	char	line[1000];
	int		len;
	int		j;

	if (!read_line(fd, line, sizeof(line)))
		return (0);
	len = ft_strlen(line);
	if (row_index == 0)
		map->cols = len;
	else if (len != map->cols)
		return (0);
	map->grid[row_index] = malloc(map->cols + 1);
	if (!map->grid[row_index])
		return (0);
	j = 0;
	while (j < len)
	{
		if (line[j] != map->empty && line[j] != map->obstacle)
			return (0);
		map->grid[row_index][j] = line[j];
		j++;
	}
	map->grid[row_index][j] = '\0';
	return (1);
}

int	fill_grid(int fd, t_map *map)
{
	int		i;

	map->grid = malloc(sizeof(char *) * map->rows);
	if (!map->grid)
		return (0);
	i = 0;
	while (i < map->rows)
	{
		if (!store_row(fd, map, i))
			return (0);
		i++;
	}
	return (1);
}

t_map	*parse_map(char *filepath)
{
	char	buf[100];
	int		fd;
	t_map	*map;
	int		i;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	i = 0;
	while (read(fd, &buf[i], 1) && buf[i] != '\n' && i < 99)
		i++;
	buf[i] = '\0';
	if (i < 4)
		return (NULL);
	map->full = buf[--i];
	map->obstacle = buf[--i];
	map->empty = buf[--i];
	buf[i] = '\0';
	map->rows = ft_atoi(buf);
	if (map->rows <= 0 || map->empty == map->obstacle
		|| map->empty == map->full || map->obstacle == map->full)
		return (NULL);
	if (!fill_grid(fd, map))
		return (NULL);
	return (map);
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