/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:02:07 by rastie            #+#    #+#             */
/*   Updated: 2023/03/23 20:46:00 by rastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	get_player_coos(t_vars *vars)
{
	vars->player->x = 0;
	while (vars->map[vars->player->x])
	{
		vars->player->y = 0;
		while (vars->map[vars->player->x][vars->player->y])
		{
			if (vars->map[vars->player->x][vars->player->y] == 'P')
				return ;
			vars->player->y++;
		}
		vars->player->x++;
	}
}

int	init_player(t_vars *vars)
{
	int			x;
	int			y;

	vars->player = malloc(sizeof (t_sprite));
	if (!vars->player)
		return (-1);
	vars->player_right = mlx_xpm_file_to_image(vars->mlx,
			"asset/img/sprite_char.xpm", &x, &y);
	if (!vars->player_right)
		return (-1);
	vars->player_left = mlx_xpm_file_to_image(vars->mlx,
			"asset/img/left_sprite_char.xpm", &x, &y);
	if (!vars->player_right)
		return (-1);
	vars->player->img = vars->player_right;
	get_player_coos(vars);
	if (solve_map(vars->map, vars))
		return (-1);
	vars->player->x = (vars->player->x - vars->offsetx)
		* vars->player->img->height;
	vars->player->y = (vars->player->y - vars->offsety)
		* vars->player->img->width;
	vars->step = 0;
	return (0);
}

int	init_map(t_vars *vars)
{
	vars->map = get_map(vars->mappath);
	if (!vars->map)
		return (-1);
	if (parse_map(vars->map, vars))
		return (-1);
	return (0);
}

int	init_win(t_vars *vars)
{
	if (init_map(vars))
		return (-1);
	vars->wwidth = int_min(vars->swidth,
			vars->lenline * vars->background->width);
	vars->wheight = int_min(vars->sheight,
			vars->nbline * vars->background->height);
	vars->wheight = 720;
	vars->wwidth = 1080;
	if (vars->wwidth < (vars->lenline * vars->x)
		|| vars->wheight < (vars->nbline * vars->y))
		get_offset(vars);
	if (init_player(vars))
		return (-1);
	vars->win = mlx_new_window(vars->mlx, vars->wwidth, vars->wheight,
			"So Long");
	if (!vars->win)
		return (-1);
	return (0);
}

int	init_vars(t_vars *vars)
{
	if (!vars)
		return (-1);
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (-1);
	vars->exit = mlx_xpm_file_to_image(vars->mlx,
			"asset/img/exit.xpm", &(vars->x), &(vars->y));
	if (!vars->exit)
		return (-1);
	vars->coin = mlx_xpm_file_to_image(vars->mlx,
			"asset/img/coin.xpm", &(vars->x), &(vars->y));
	if (!vars->coin)
		return (-1);
	vars->wall = mlx_xpm_file_to_image(vars->mlx,
			"asset/img/wall.xpm", &(vars->x), &(vars->y));
	if (!vars->wall)
		return (-1);
	vars->background = mlx_xpm_file_to_image(vars->mlx,
			"asset/img/void.xpm", &(vars->x), &(vars->y));
	if (!vars->background)
		return (-1);
	mlx_get_screen_size(vars->mlx, &(vars->swidth), &(vars->sheight));
	if (!vars->swidth || !vars->sheight)
		return (-1);
	return (init_win(vars));
}
