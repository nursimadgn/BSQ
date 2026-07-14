#include "bsq.h"

// İlk satırdaki parametreleri (örn: "9.ox") parse eden fonksiyon
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
	if (map->rows <= 0 || map->empty == map->obstacle 
		|| map->empty == map->full || map->obstacle == map->full)
		return (0);
	return (1);
}

// Map matrisini serbest bırakan bellek temizliği
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

// Bu fonksiyon dosya yolunu alıp t_map struct'ını doldurur
// Basitleştirilmiş gösterimdir; satır uzunluk doğrulamaları eklenmelidir.
t_map	*parse_map(char *filepath)
{
	int		fd;
	t_map	*map;
	int		i;

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
	map->grid = malloc(sizeof(char *) * map->rows);
	// Satırları okuma ve haritaya yazma mantığı buraya gelir...
	close(fd);
	return (map);
}