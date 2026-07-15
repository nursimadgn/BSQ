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

/* utils.c */
void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_puterror(void);
int		ft_atoi(char *str);
int		ft_strlen(char *str);

/* map_parser.c */
t_map	*parse_map(char *filepath);
void	free_map(t_map *map);
int	ft_strcmp(char *s1, char *s2);
void	solve_bsq(t_map *map);
int     read_loop(int fd, char *line, int size, int *ret);
void    flush_line(int fd);
int     validate_row(char *line, t_map *map, int index);

#endif