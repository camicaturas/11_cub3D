/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/07/31 15:39:39 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"
/*
int	check_tilesize(t_struct *game_struct)
{
	if (game_struct->map_width * game_struct->map_tile_width
		> game_struct->screen_width
		|| game_struct->map_height * game_struct->map_tile_height
		> game_struct->screen_height)
		return (0);
	return (1);
}
*/

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}

/*

void	validate_map_chars(t_struct *game_struct)
{
	int		x;
	int		y;
	char	**map;

	map = game_struct->minimap.map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '\n')
			{
				x++;
				continue;
			}
			if (!is_valid_map_char(map[y][x]))
			{
				printf("\033[1;33mInvalid character '%c' found at line %d, "
					"column %d.\033[0m\n", map[y][x], y + 1, x + 1);
				error_controller(game_struct, INVALID_MAP_CHAR);
			}
			x++;
		}
		y++;
	}
}

*/

void	validate_map_chars(t_struct *game_struct)
{
	int		x;
	int		y;
	char	**map;

	map = game_struct->minimap.map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] != '\n' && !is_valid_map_char(map[y][x]))
			{
				printf("\033[1;33mInvalid character '%c' found at line %d, "
					"column %d.\033[0m\n", map[y][x], y + 1, x + 1);
				error_controller(game_struct, INVALID_MAP_CHAR);
			}
			x++;
		}
		y++;
	}
}

void	map_controller(t_struct *game_struct)
{
	int	x;
	int	y;
	char spawn_type;

	y = game_struct->minimap.player_grid_y;
	x = game_struct->minimap.player_grid_x;
	spawn_type = game_struct->minimap.nswe;
	if (spawn_type == 'N' || spawn_type == 'E'
		|| spawn_type == 'S' || spawn_type == 'W')
	{
			flood_fill(y, x, game_struct);
			restore_map(game_struct);
	}
	else
		error_controller(game_struct, NO_PLAYER_SPAWN);
}
