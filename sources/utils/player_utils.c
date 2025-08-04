/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/07/31 15:18:50 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	set_player_grid_position(t_minimap *map, int x, int y)
{
	map->player_grid_x = x;
	map->player_grid_y = y;
}

double	normalize_angle(double angle)
{
	if (angle < 0)
		angle += (2 * PI);
	if (angle > (2 * PI))
		angle -= (2 * PI);
	return (angle);
}

bool	rotate_player(t_struct *game_struct, int key)
{
	if (key == MLX_KEY_LEFT)
	{
		game_struct->player.radians -= ROTATION_SPEED;
		game_struct->player.radians =
			normalize_angle(game_struct->player.radians);
		return (true);
	}
	if (key == MLX_KEY_RIGHT)
	{
		game_struct->player.radians += ROTATION_SPEED;
		game_struct->player.radians =
			normalize_angle(game_struct->player.radians);
		return (true);
	}
	return (false);
}
