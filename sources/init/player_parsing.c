/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/07/31 15:19:24 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	init_player_direction(t_player *player, char nswe)
{
	if (nswe == 'E' || nswe == 'W')
	{
		if (nswe == 'E')
			player->radians = 0;
		else if (nswe == 'W')
			player->radians = PI;
	}
	else if (nswe == 'N' ||nswe == 'S')
	{
		if (nswe == 'N')
			player->radians = 3 * PI05;
		else if (nswe == 'S')
			player->radians = PI05;
	}
}

static	int	check_and_store_spawn(t_struct *game, char **map,
	int y, int x, int spawns_amount)
{
	if (ft_strchr("NSWE", map[y][x]))
	{
		game->minimap.player_grid_x = x;
		game->minimap.player_grid_y = y;
		game->minimap.nswe = map[y][x];
		init_player_direction(&game->player, game->minimap.nswe);
		map[y][x] = '0';
		spawns_amount++;
	}
	return spawns_amount;
}

void	parse_player_spawn_position(t_struct *game, char **map)
{
	int	spawns_amount;
	int	y;
	int	x;

	y = 0;
	spawns_amount = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			spawns_amount = check_and_store_spawn(
				game, map, y, x, spawns_amount);
			x++;
		}
		y++;
	}
	if (spawns_amount > 1)
		error_controller(game, MULTI_SPAWNS);
}

/*
void	parse_player_spawn_position(t_struct *game, char **map)
{
	int	spawns_amount;
	int	y;
	int	x;

	y = 0;
	spawns_amount = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_strchr("NSWE", map[y][x]))
			{
				game->minimap.player_grid_x = x;
				game->minimap.player_grid_y = y;
				game->minimap.nswe = map[y][x];
				init_player_direction(&game->player, game->minimap.nswe);
				map[y][x] = '0';
				spawns_amount++;
			}
			x++;
		}
		y++;
	}
	if (spawns_amount > 1)
		error_controller(game, MULTI_SPAWNS);
}
*/