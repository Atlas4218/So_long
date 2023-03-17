/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:19:57 by rastie            #+#    #+#             */
/*   Updated: 2023/03/17 17:35:29 by rastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

int	center_player(t_vars *vars)
{
	return (vars->map[vars->offsetx + vars->wwidth / vars->x / 2]
		[vars->offsety + vars->wheight / vars->y / 2] == 'P');
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
			if (center_player(vars))
				return ;
			vars->offsety++;
		}
		vars->offsetx++;
	}
}
