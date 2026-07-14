#include "bsq.h"

// 3 sayının minimumunu bulan yardımcı fonksiyon
int	get_min(int a, int b, int c)
{
	int	min;

	min = a;
	if (b < min)
		min = b;
	if (c < min)
		min = c;
	return (min);
}

// DP tablosunu güncelleyip en büyük kareyi kaydeden fonksiyon
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
				dp[i][j] = get_min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]) + 1;
			if (dp[i][j] > best->size)
			{
				best->size = dp[i][j];
				best->y = i;
				best->x = j;
			}
		}
	}
}

// En büyük karenin içini 'full' karakteri ile dolduran fonksiyon
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

// Çözücü ana fonksiyon
void	solve_bsq(t_map *map)
{
	int			**dp;
	t_square	best;
	int			i;

	best.size = 0;
	best.x = 0;
	best.y = 0;
	
	// DP matrisi için yer ayrılması (malloc)
	dp = malloc(sizeof(int *) * map->rows);
	i = 0;
	while (i < map->rows)
	{
		dp[i] = malloc(sizeof(int) * map->cols);
		i++;
	}

	find_biggest(map, dp, &best);
	draw_square(map, best);

	// DP matrisinin free edilmesi
	i = 0;
	while (i < map->rows)
		free(dp[i++]);
	free(dp);
}