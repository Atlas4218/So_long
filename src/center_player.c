/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:19:57 by rastie            #+#    #+#             */
/*   Updated: 2023/03/23 20:46:36 by rastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

int	center_player(t_vars *vars)
{
	return (vars->map[vars->offsetx + vars->wwidth / vars->x / 2]
		[vars->offsety + vars->wheight / vars->y / 2] == 'P');
}

int	player_in_window(t_vars *vars)
{
	int	x;
	int	y;

	if (center_player(vars))
		return (1);
	x = vars->offsetx;
	while (x < vars->offsetx + vars->wwidth / vars->x)
	{
		y = vars->offsety;
		while (y < vars->offsety + vars->wheight / vars->y)
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
		while (vars->map[vars->offsetx]
			[vars->offsety])
		{
			if (player_in_window(vars))
				return ;
			vars->offsety++;
		}
		vars->offsetx++;
	}
}
