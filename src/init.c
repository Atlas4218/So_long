/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:02:07 by rastie            #+#    #+#             */
/*   Updated: 2023/03/17 19:49:25 by rastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

int	init_win(t_vars *vars)
{
	vars->wwidth = int_min(vars->swidth,
			vars->lenline * vars->background->width);
	vars->wheight = int_min(vars->sheight,
			vars->nbline * vars->background->height);
	vars->wheight = 720;
	vars->wwidth = 1080;
	vars->win = mlx_new_window(vars->mlx, vars->wwidth, vars->wheight,
			"So Long");
	if (!vars->win)
		return (closer(vars));
	return (0);
}

int	init_map(t_vars *vars)
{
	vars->map = get_map(vars->mappath);
	if (!vars->map)
		return (closer(vars));
	if (parse_map(vars->map, vars))
		return (closer(vars));
	if (vars->wwidth < (vars->lenline * vars->x)
		|| vars->wheight < (vars->nbline * vars->y))
		get_offset(vars);
	return (0);
}

int	init_player(t_vars *vars)
{
	t_sprite	*player;
	int			x;
	int			y;

	player = malloc(sizeof (t_sprite));
	player->x = 0;
	player->y = 0;
	vars->player_right = mlx_xpm_file_to_image(vars->mlx,
			"asset/img/sprite_char.xpm", &x, &y);
	if (!vars->player_right)
		return (closer(vars));
	vars->player_left = mlx_xpm_file_to_image(vars->mlx,
			"asset/img/left_sprite_char.xpm", &x, &y);
	if (!vars->player_right)
		return (closer(vars));
	player->img = vars->player_right;
	vars->player = player;
	if (init_map(vars))
		return (-1);
	player->x = (player->x - vars->offsety) * player->img->height;
	player->y = (player->y - vars->offsetx) * player->img->width;
	vars->step = 0;
	return (init_win(vars));
}

int	init_vars(t_vars *vars)
{
	if (!vars)
		return (-1);
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (closer(vars));
	vars->exit = mlx_xpm_file_to_image(vars->mlx,
			"asset/img/exit.xpm", &(vars->x), &(vars->y));
	if (!vars->exit)
		return (closer(vars));
	vars->coin = mlx_xpm_file_to_image(vars->mlx,
			"asset/img/coin.xpm", &(vars->x), &(vars->y));
	if (!vars->coin)
		return (closer(vars));
	vars->wall = mlx_xpm_file_to_image(vars->mlx,
			"asset/img/wall.xpm", &(vars->x), &(vars->y));
	if (!vars->wall)
		return (closer(vars));
	vars->background = mlx_xpm_file_to_image(vars->mlx,
			"asset/img/void.xpm", &(vars->x), &(vars->y));
	if (!vars->background)
		return (closer(vars));
	mlx_get_screen_size(vars->mlx, &(vars->swidth), &(vars->sheight));
	if (!vars->swidth || !vars->sheight)
		return (closer(vars));
	return (init_player(vars));
}
