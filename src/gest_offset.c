/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_offset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:19:57 by rastie            #+#    #+#             */
/*   Updated: 2023/03/28 16:24:58 by rastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

int	int_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	change_offset(t_vars *vars, int *x, int *y)
{
	if (*x < 0)
	{
		vars->offsetx =vars->offsetx - vars->wheight / vars->x;
		*x = vars->wheight - vars->player->img->height
			- vars->wheight % vars->y;
	}
	if (*y < 0)
	{
		vars->offsety = vars->offsety - vars->wwidth / vars->y;
		*y = vars->wwidth - vars->player->img->width
			- vars->wwidth % vars->y;
	}
	if (*x + vars->player->img->height > vars->wheight)
	{
		vars->offsetx = vars->offsetx + vars->wheight / vars->x;
		*x = 0;
	}
	if (*y + vars->player->img->width > vars->wwidth)
	{
		vars->offsety = vars->offsety + vars->wwidth / vars->y;
		*y = 0;
	}
}

int	player_in_window(t_vars *vars)
{
	int	x;
	int	y;

	x = vars->offsetx;
	while (x - vars->offsetx < vars->wheight / vars->x && vars->map[x])
	{
		y = vars->offsety;
		while (y - vars->offsety < vars->wwidth / vars->y
			&& vars->map[x][y])
		{
			if (vars->map[x][y] == 'P')
				return (1);
			y++;
		}
		x++;
	}
	return (0);
}

void	get_offset(t_vars *vars)
{
	vars->offsetx = 0;
	while (vars->map[vars->offsetx])
	{
		vars->offsety = 0;
		while (vars->map[vars->offsetx][vars->offsety])
		{
			if (player_in_window(vars))
				return ;
			vars->offsety++;
		}
		vars->offsetx++;
	}
}
