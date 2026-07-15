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

void	process_file(char *filepath)
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
	free_map(map);
}

int	main(int argc, char **argv)
{
	int	i;

	if (argc < 2)
	{
		process_file("STDIN");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		process_file(argv[i]);
		if (i > 1) // makarayız dimi abi komediyiz dimi abi
			ft_putchar('\n');
		i++;
	}
	return (0);
}
