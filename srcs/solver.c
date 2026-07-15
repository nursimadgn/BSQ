#include "bsq.h"

// 3 sayının minimumunu bulan yardımcı fonksiyon
static int	get_min(int a, int b, int c) // min değer alıyor vay canına
{
	int	min;

	min = a;
	if (b < min)
		min = b;
	if (c < min)
		min = c;
	return (min);
}

void	update_best(int **dp, t_square *best, int i, int j)
{
	if (dp[i][j] > best->size)
	{
		best->size = dp[i][j];
		best->y = i;
		best->x = j;
	}
}

void	find_biggest(t_map *map, int **dp, t_square *best)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			if (map->grid[i][j] == map->obstacle)
				dp[i][j] = 0;
			else if (i == 0 || j == 0)
				dp[i][j] = 1;
			else
				dp[i][j] = get_min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1])
					+ 1;
			update_best(dp, best, i, j);
		}
	}
}

void	draw_square(t_map *map, t_square best)
{
	int	i;
	int	j;

	i = best.y - best.size + 1;
	while (i <= best.y)
	{
		j = best.x - best.size + 1;
		while (j <= best.x)
		{
			map->grid[i][j] = map->full;
			j++;
		}
		i++;
	}
}

void	solve_bsq(t_map *map)
{
	int			**dp;
	t_square	best;
	int			i;

	best.size = 0;
	best.x = 0;
	best.y = 0;
	dp = malloc(sizeof(int *) * map->rows);
	if (!dp)
		return ;
	i = 0;
	while (i < map->rows)
	{
		dp[i] = malloc(sizeof(int) * map->cols);
		if (!dp[i])
			return ;
		i++;
	}
	find_biggest(map, dp, &best);
	draw_square(map, best);
	i = 0;
	while (i < map->rows)
		free(dp[i++]);
	free(dp);
}
