/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:54:27 by rastie            #+#    #+#             */
/*   Updated: 2023/03/17 14:35:19 by rastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "so_long.h"

int	parse_room(char *line, t_vars *vars)
{
	int	lenline;
	int	i;

	i = 0;
	lenline = strlen(line);
	while (line[i])
	{
		if (line[i] == 'C')
			vars->nbcoin++;
		else if (line[i] == 'E')
			vars->nbexit++;
		else if (line[i] == 'P')
			vars->nbplayer++;
		else if (line[i] != '0' && line[i] != '1')
			return (printf(CHARACTERERROR));
		i++;
	}
	if (!(line[0] == '1' && line[lenline - 1] == '1'))
		return (printf(WALLERROR));
	return (0);
}

int	parse_floor_ceiling(char *line)
{
	while (*line)
	{
		if (*line != '1')
			return (1);
		line++;
	}
	return (0);
}

int	fill_map(int nbcoin, char **map, int i, int j)
{
	if (map[i][j] == '1' || map[i][j] == 'R'
			|| map[i][j] == 'V' || map[i][j] == 'S')
		return (0);
	if (map[i][j] == '0')
		map[i][j] = 'R';
	if (map[i][j] == 'C')
	{
		map[i][j] = 'V';
		nbcoin++;
	}
	if (map[i][j] == 'E')
		map[i][j] = 'S';
	fill_map(nbcoin, map, i + 1, j);
	fill_map(nbcoin, map, i - 1, j);
	fill_map(nbcoin, map, i, j + 1);
	fill_map(nbcoin, map, i, j - 1);
	return (0);
}

int	solve_map(char **map, t_vars *vars)
{
	if (!vars || !map || !*map)
		return (5);
	vars->player->y = 0;
	while (map[vars->player->y])
	{
		vars->player->x = 0;
		while (map[vars->player->y][vars->player->x])
		{
			if (map[vars->player->y][vars->player->x] == 'P')
				break ;
			vars->player->x++;
		}
		if (map[vars->player->y][vars->player->x] == 'P')
			break ;
		vars->player->y++;
	}
	fill_map(0, map, vars->player->y, vars->player->x);
	while (*map)
	{
		if (strchr(*map, 'E') || strchr(*map, 'C'))
			return (printf(RESOLUTIONERROR));
		map++;
	}
	return (0);
}

int	parse_map(char **map, t_vars *vars)
{
	if (!vars || !map || !*map)
		return (6);
	vars->nbcoin = 0;
	vars->nbplayer = 0;
	vars->nbexit = 0;
	vars->nbline = 0;
	vars->lenline = strlen(map[vars->nbline]);
	if (parse_floor_ceiling(map[vars->nbline++]))
		return (printf(WALLERROR));
	while (map[vars->nbline])
	{
		if (vars->lenline != (int)strlen(map[vars->nbline]))
			return (printf(FORMERROR));
		if (parse_room(map[vars->nbline], vars))
			return (4);
		vars->nbline++;
	}
	if (parse_floor_ceiling(map[vars->nbline - 1]))
		return (printf(WALLERROR));
	if (!vars->nbcoin || vars->nbplayer != 1 || vars->nbexit != 1)
		return (printf(NUMBERERROR));
	return (solve_map(map, vars));
}
