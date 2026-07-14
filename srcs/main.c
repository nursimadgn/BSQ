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

void	process_file(char *filepath, int multi)
{
	t_map	*map;

	map = parse_map(filepath);
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

	if (argc < 2)
	{
		// Standart inputtan (stdin) okuma fonksiyonu çağrılmalı
		// Örn: process_stdin();
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		process_file(argv[i], (argc > 2 && i < argc - 1));
		i++;
	}
	return (0);
}