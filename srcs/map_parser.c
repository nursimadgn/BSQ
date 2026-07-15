#include "bsq.h"

int	read_line(int fd, char *line, int size) // line hafızaya alınıyor
{
	int	i;
	int	ret;

	i = read_loop(fd, line, size, &ret); //\n ve\r(windows yüzünden) atlıyor
	if (ret <= 0 && i == 0)
		return (0);
	if (i == size - 1)
	{
		flush_line(fd); // bunu düzelet daha flsuh line fonksiyonuna git *****
		return (0);
	}
	line[i] = '\0';
	return (1);
}

int	fill_row(int fd, t_map *map, int index) // dongude surekli çalışıyor eğer ilkiyse index değeri 0
{
	char	line[1000]; // burayi dinamik yapasım var ama götüm yemiyor
	int		len;

	if (!read_line(fd, line, sizeof(line)))
		return (0);
	len = ft_strlen(line);
	if (index == 0)
		map->cols = len;       // ilk satırdan aldık cols değerini
	else if (len != map->cols) // cols uzunluk kontrolu iyii
		return (0);
	map->grid[index] = malloc(map->cols + 1);
	if (!map->grid[index])
		return (0);
	if (!validate_row(line, map, index))// çokomelli mapin sadece empty ve obstacledan oluştuğundan emin oluyor
	{
		free(map->grid[index]);
		return (0);
	}
	return (1);
}

int	fill_grid(int fd, t_map *map) // asagiya açıklama yazdım
{
	int	i;

	map->grid = malloc(sizeof(char *) * map->rows);
	if (!map->grid)
		return (0);
	i = 0;
	while (i < map->rows)
		map->grid[i++] = NULL;
	i = 0;
	while (i < map->rows)
	{
		if (!fill_row(fd, map, i))
		{
			while (i >= 0)
			{
				free(map->grid[i]);
				i--;
			}
			free(map->grid);
			map->grid = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}

int	parse_header(int fd, t_map *map) // header bilgi okuma
{
	char	buf[100];
	int		i;

	if (!read_line(fd, buf, sizeof(buf)))
		return (0);
	i = ft_strlen(buf);
	if (i < 4)
		return (0);
	map->full = buf[--i];
	map->obstacle = buf[--i];
	map->empty = buf[--i];
	buf[i] = '\0';
	map->rows = ft_atoi(buf);
	// atoiyi değiştim artık harf gorurse hata sayıp 0 donduruyor
	return (map->rows > 0 && map->empty != map->obstacle
		&& map->empty != map->full && map->obstacle != map->full);
}

t_map	*parse_map(char *filepath)
{
	int		fd;
	t_map	*map;

	if (!ft_strcmp(filepath, "STDIN"))
		fd = STDIN_FILENO;
	else
		fd = open(filepath, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map = (t_map *)malloc(sizeof(t_map));
	if (!map || !parse_header(fd, map)) // headerdaki bilgileri okuma
	{
		close(fd);
		free(map);
		return (NULL);
	} // fill gridse az veya çok rows kontrolu ekleyek
	if (!fill_grid(fd, map))
	// gridi mallocluyor mapı kontrol(empty,obstacle) ediyor
	{
		close(fd);
		free_map(map);
		return (NULL);
	}
	close(fd);
	return (map);
}