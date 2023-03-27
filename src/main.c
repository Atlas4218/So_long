/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:32:48 by rastie            #+#    #+#             */
/*   Updated: 2023/03/27 20:00:30 by rastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Include so_long
#include "so_long.h"

void	clear_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

int	clear_player(t_vars *vars)
{
	if (vars->player)
		free(vars->player);
	if (vars->player_left)
		mlx_destroy_image(vars->mlx, vars->player_left);
	if (vars->player_right)
		mlx_destroy_image(vars->mlx, vars->player_right);
	return (0);
}

int	closer(t_vars *vars)
{
	printf("(Bye)> ヾ(＾ ∇ ＾).\n");
	if (vars->map)
		clear_map(vars->map);
	if (vars->background)
		mlx_destroy_image(vars->mlx, vars->background);
	if (vars->exit)
		mlx_destroy_image(vars->mlx, vars->exit);
	if (vars->coin)
		mlx_destroy_image(vars->mlx, vars->coin);
	if (vars->wall)
		mlx_destroy_image(vars->mlx, vars->wall);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	clear_player(vars);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
	return (5);
}

int	handle_keyevent(int keycode, t_vars *vars)
{
	int			move;

	move = 0;
	if (keycode == XK_Escape)
		closer(vars);
	if (keycode == XK_a || keycode == XK_Left)
		if (vars->player->img)
			move += move_left(vars, vars->player);
	if (keycode == XK_w || keycode == XK_Up)
		if (vars->player->img)
			move += move_up(vars, vars->player);
	if (keycode == XK_s || keycode == XK_Down)
		if (vars->player->img)
			move += move_down(vars, vars->player);
	if (keycode == XK_d || keycode == XK_Right)
		if (vars->player->img)
			move += move_right(vars, vars->player);
	vars->step += int_abs(move);
	if (move)
		printf("%d\n", vars->step);
	if (move == -1)
		closer(vars);
	return (0);
}

int	main(int ac, char **av)
{
	t_vars		vars;

	if (ac != 2)
	{
		errno = 22;
		return (perror("Erreur"), errno);
	}
	vars.mappath = av[1];
	if (init_vars(&vars))
		return (closer(&vars));
	render_room(&vars);
	render_sprite(&vars, vars.player);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, closer, &vars);
	mlx_hook(vars.win, KeyPress, KeyPressMask, handle_keyevent, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
