/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:08:29 by rastie            #+#    #+#             */
/*   Updated: 2023/03/28 16:49:18 by rastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SO_LONG_H
# define SO_LONG_H
//Header mlx
# include "mlx.h"
# include "mlx_int.h"
//Includes X11, utilise pour les macros
# include <X11/X.h>
# include <X11/keysym.h>
//Includes standards
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "get_next_line.h"
# include "libft.h"
# define RESER "Error\nMap cannot be solved\n"
# define WALLER "Error\nThe map isn't closed by walls: line %d\n"
# define FORMER "Error\nThe map isn't rectangular: line %d\n"
# define NBER "Error\nWrong  number of element: %d coin, %d exit, %d player\n"
# define CHARER "Error\nNon recognized character in the map: %c\n"

typedef struct s_sprite
{
	int		x;
	int		y;
	t_img	*img;
}	t_sprite;
typedef struct s_vars
{
	void		*mlx;
	void		*win;
	char		*mappath;
	char		**map;
	int			wwidth;
	int			wheight;
	int			swidth;
	int			sheight;
	int			x;
	int			y;
	int			offsetx;
	int			offsety;
	int			step;
	int			nbcoin;
	int			nbplayer;
	int			nbexit;
	int			nbline;
	int			lenline;
	t_img		*background;
	t_img		*exit;
	t_img		*coin;
	t_img		*wall;
	t_img		*player_left;
	t_img		*player_right;
	t_sprite	*player;
}	t_vars;
int		init_vars(t_vars *vars);
int		closer(t_vars *vars);
int		move_up(t_vars *vars, t_sprite *sprite);
int		move_left(t_vars *vars, t_sprite *sprite);
int		move_down(t_vars *vars, t_sprite *sprite);
int		move_right(t_vars *vars, t_sprite *sprite);
int		render_sprite(t_vars *vars, t_sprite *sprite);
void	render_room(t_vars *vars);
void	get_offset(t_vars *vars);
void	change_offset(t_vars *vars, int *x, int *y);
int		parse_room(char *line, t_vars *vars);
int		parse_floor_ceiling(char *line);
int		parse_map(char **map, t_vars *vars);
int		fill_map(int nbcoin, char **map, int i, int j);
int		solve_map(char **map, t_vars *vars);
char	**get_map(char *filename);
void	**list_to_array(t_list *list);
int		int_abs(int nb);
int		int_min(int a, int b);
#endif
