/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:25:56 by rastie            #+#    #+#             */
/*   Updated: 2023/03/17 15:39:14 by rastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

int	render_sprite(t_vars *vars, t_sprite *sprite)
{
	if (!sprite || !(sprite->img) || !vars || !(vars->mlx) || !(vars->win))
		return (1);
	mlx_put_image_to_window(vars->mlx, vars->win, sprite->img,
		sprite->x, sprite->y);
	return (0);
}

void	render_elements(t_vars *vars, int offset_x, int offset_y)
{
	int		i;
	int		j;

	j = 0;
	while (vars->map[j + offset_x] && j * vars->x < vars->wheight)
	{
		i = 0;
		while (vars->map[j + offset_x][i + offset_y]
				&& i * vars->y < vars->wwidth)
		{
			if (vars->map[j + offset_x][i + offset_y] == 'V')
				mlx_put_image_to_window(vars->mlx, vars->win,
					vars->coin, i * vars->x, j * vars->y);
			if (vars->map[j + offset_x][i + offset_y] == '1')
				mlx_put_image_to_window(vars->mlx, vars->win,
					vars->wall, i * vars->x, j * vars->y);
			if (vars->map[j + offset_x][i + offset_y] == 'S')
				mlx_put_image_to_window(vars->mlx, vars->win,
					vars->exit, i * vars->x, j * vars->y);
			i++;
		}
		j++;
	}
}

void	render_background(t_vars *vars)
{
	int	i;
	int	j;

	if (!vars->win)
		return ;
	i = 0;
	while (i < vars->wwidth)
	{
		j = 0;
		while (j < vars->wheight)
		{
			mlx_put_image_to_window(vars->mlx, vars->win,
				vars->background, i, j);
			j += vars->background->height;
		}
		i += vars->background->width;
	}
}

void	render_room(t_vars *vars)
{
	render_background(vars);
	render_elements(vars, vars->offsetx, vars->offsety);
}
