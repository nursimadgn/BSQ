#include "bsq.h"

void	print_grid(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->rows)
	{
		ft_putstr(map->grid[i]);
		ft_putchar('\n');
		i++;
	}
}

void	process_map(int fd, int multi)
{
	t_map	*map;

	map = parse_map(fd);
	if (!map)
	{
		ft_puterror();
		return ;
	}
	solve_bsq(map);
	print_grid(map);
	if (multi)
		ft_putchar('\n');
	free_map(map);
}

int	main(int argc, char **argv)
{
	int	i;
	int	fd;

	
	if (argc < 2)
	{
		process_map(0, 0); 
		return (0);
	}
	
	i = 1;
	while (i < argc)
	{
		fd = open(argv[i], O_RDONLY);
		if (fd < 0)
			ft_puterror();
		else
		{
			process_map(fd, (argc > 2 && i < argc - 1));
			close(fd);
		}
		i++;
	}
	return (0);
}