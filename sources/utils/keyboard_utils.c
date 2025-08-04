/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/07/31 15:19:01 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

bool	is_walkable(t_struct *game_struct, int y, int x)
{
	if (y < 0 || y > game_struct->minimap.map_height
		|| x < 0 || x > game_struct->minimap.map_width)
		return (false);
	if (game_struct->minimap.map[y][x] == '1')
		return (false);
	return (true);
}

void	normalize_movement(t_struct *game_struct)
{
	double	len;

	len = sqrt(game_struct->player.move.x * game_struct->player.move.x
		+ game_struct->player.move.y * game_struct->player.move.y);
	if (len > 0)
	{
		game_struct->player.move.x = (game_struct->player.move.x / len)
			* PLAYER_SPEED;
		game_struct->player.move.y = (game_struct->player.move.y / len)
			* PLAYER_SPEED;
	}
}

void	ft_player_movement(t_struct *game_struct)
{
	double	next_pos_x;
	double	next_pos_y;
	int grid_x;
	int grid_y;

	next_pos_x = game_struct->player.pos.x + game_struct->player.move.x;
	next_pos_y = game_struct->player.pos.y + game_struct->player.move.y;
	grid_x = (int)(next_pos_x / TILE_SIZE);
	grid_y = (int)(game_struct->player.pos.y / TILE_SIZE);
	if (is_walkable(game_struct, grid_y, grid_x))
		game_struct->player.pos.x = next_pos_x;
	grid_y = (int)(next_pos_y / TILE_SIZE);
	grid_x = (int)(game_struct->player.pos.x / TILE_SIZE);
	if (is_walkable(game_struct, grid_y, grid_x))
		game_struct->player.pos.y = next_pos_y;
}
