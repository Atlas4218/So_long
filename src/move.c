/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:40:53 by rastie            #+#    #+#             */
/*   Updated: 2023/03/27 16:34:10 by rastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"


int	move_sprite(t_vars *vars, t_sprite *sprite, int x, int y)
{
	x = x * sprite->img->height + sprite->x;
	y = y * sprite->img->width + sprite->y;
	if (!sprite || !(sprite->img) || !vars || !(vars->background))
		return (0);
	if (vars->map[x / sprite->img->height + vars->offsetx]
		[y / sprite->img->width + vars->offsety] == '1')
		return (0);
	if (vars->map[sprite->x / sprite->img->height + vars->offsetx]
		[sprite->y / sprite->img->width + vars->offsety] == 'V')
	{
		vars->map[sprite->x / sprite->img->height + vars->offsetx]
		[sprite->y / sprite->img->width + vars->offsety] = 'R';
		vars->nbcoin--;
	}
	if (vars->map[x / sprite->img->height + vars->offsetx]
		[y / sprite->img->width + vars->offsety] == 'S'
		&& !vars->nbcoin)
		return (-1);
	change_offset(vars, &x, &y);
	sprite->x = x;
	sprite->y = y;
	return (render_room(vars), 1);
}

int	move_up(t_vars *vars, t_sprite *sprite)
{
	return (move_sprite(vars, sprite, -1, 0));
}

int	move_down(t_vars *vars, t_sprite *sprite)
{
	return (move_sprite(vars, sprite, 1, 0));
}

int	move_left(t_vars *vars, t_sprite *sprite)
{
	sprite->img = vars->player_left;
	return (move_sprite(vars, sprite, 0, -1));
}

int	move_right(t_vars *vars, t_sprite *sprite)
{
	sprite->img = vars->player_right;
	return (move_sprite(vars, sprite, 0, 1));
}
