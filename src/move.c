/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:40:53 by rastie            #+#    #+#             */
/*   Updated: 2023/03/15 18:25:25 by rastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

int	move_sprite(t_vars *vars, t_sprite *sprite, int x, int y)
{
	x = x * sprite->img->width + sprite->x;
	y = y * sprite->img->height + sprite->y;
	if (!sprite || !(sprite->img) || !vars || !(vars->background))
		return (0);
	if (vars->map[y / sprite->img->width][x / sprite->img->height] == '1')
		return (0);
	if (vars->map[sprite->y / sprite->img->width]
		[sprite->x / sprite->img->height] == 'V')
	{
		vars->map[sprite->y / sprite->img->width]
		[sprite->x / sprite->img->height] = 'R';
		vars->nbcoin--;
	}
	if (vars->map[y / sprite->img->width][x / sprite->img->height] == 'S'
			&& !vars->nbcoin)
		return (-1);
	if (x < 0 || y < 0 || x + sprite->img->width > vars->wwidth
		|| y + sprite->img->height > vars->wheight)
		return (0);
	sprite->x = x;
	sprite->y = y;
	render_room(vars);
	render_sprite(vars, sprite);
	return (1);
}

int	move_up(t_vars *vars, t_sprite *sprite)
{
	return (move_sprite(vars, sprite, 0, -1));
}

int	move_down(t_vars *vars, t_sprite *sprite)
{
	return (move_sprite(vars, sprite, 0, 1));
}

int	move_left(t_vars *vars, t_sprite *sprite)
{
	sprite->img = vars->player_left;
	return (move_sprite(vars, sprite, -1, 0));
}

int	move_right(t_vars *vars, t_sprite *sprite)
{
	sprite->img = vars->player_right;
	return (move_sprite(vars, sprite, 1, 0));
}
