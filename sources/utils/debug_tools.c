/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/05/27 15:20:21 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void print_map_on_console(t_struct *game_struct)
{
	if (!game_struct->minimap.map || !game_struct->minimap.map)
	{
		printf("ERROR: map_struct or map_struct->map is NULL\n");
		return;
	}

	int y = 0;
	while (game_struct->minimap.map[y])
	{
		printf("%s", game_struct->minimap.map[y]);
		y++;
	}
}

void player_current_grid_pos(t_minimap *map)
{
	printf("Player is in grid cell: (%d, %d)\n", map->player_grid_x, map->player_grid_y);
}

// this draw a green line from the center of the player marking the direction
void	draw_degub_green_line_direction(t_struct *game_struct)
{
	int	center_x = game_struct->player.pos.x * MINIMAP_TILE_SIZE;
	int	center_y = game_struct->player.pos.y * MINIMAP_TILE_SIZE;

	int i = 0;
	// Draw green direction line from the center of the player
	double	radians = game_struct->player.radians;
	int		line_length = 100;
	i = -1;
	while (++i < line_length)
	{
		int	px = center_x + MINIMAP_PLAYER_SIZE / 2 + cos(radians) * i;
		int	py = center_y + MINIMAP_PLAYER_SIZE / 2 + sin(radians) * i;

		if (px >= 0 && px < (game_struct->minimap.map_width * MINIMAP_TILE_SIZE) &&
			py >= 0 && py < (game_struct->minimap.map_height * MINIMAP_TILE_SIZE))
		{
			mlx_put_pixel(game_struct->minimap_img, px, py, GREEN);
		}
	}
}