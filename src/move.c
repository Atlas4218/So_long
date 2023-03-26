/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:40:53 by rastie            #+#    #+#             */
/*   Updated: 2023/03/26 20:26:00 by rastie           ###   ########.fr       */
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
		vars->offsetx = int_max(0, vars->offsetx - vars->wheight / vars->x);
		*x = vars->wheight - vars->player->img->height
			- vars->wheight % vars->y;
	}
	if (*y < 0)
	{
		vars->offsety = int_max(0, vars->offsety - vars->wwidth / vars->y);
		*y = vars->wwidth - vars->player->img->width
			- vars->wwidth % vars->y;
	}
	if (*x + vars->player->img->height > vars->wheight)
	{
		vars->offsetx = int_min(vars->offsetx + vars->wheight / vars->x,
				vars->nbline - vars->wheight / vars->x);
		*x = 0;
	}
	if (*y + vars->player->img->width > vars->wwidth)
	{
		vars->offsety = int_min(vars->offsety + vars->wwidth / vars->y,
				vars->lenline - vars->wwidth / vars->y);
		*y = 0;
	}
}
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
