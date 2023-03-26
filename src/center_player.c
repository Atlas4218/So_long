/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:19:57 by rastie            #+#    #+#             */
/*   Updated: 2023/03/26 17:25:02 by rastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

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
