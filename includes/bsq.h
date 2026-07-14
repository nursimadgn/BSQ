/*
** EPITECH PROJECT, 2026
** bsq
** File description:
** Header for the BSQ project
*/

#ifndef BSQ_H
# define BSQ_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_map
{
	int		rows;
	int		cols;
	char	empty;
	char	obstacle;
	char	full;
	char	**grid;
}	t_map;

typedef struct s_square
{
	int	size;
	int	x;
	int	y;
}	t_square;

void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_puterror(void);
int		ft_atoi(char *str);
int		ft_strlen(char *str);
t_map    *parse_map(int fd);
void	free_map(t_map *map);
void	solve_bsq(t_map *map);

#endif