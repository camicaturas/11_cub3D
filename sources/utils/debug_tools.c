/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/07/31 15:18:40 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	print_map_on_console(t_struct *game_struct)
{
	int y;

	if (!game_struct->minimap.map || !game_struct->minimap.map)
	{
		printf("ERROR: map_struct or map_struct->map is NULL\n");
		return ;
	}
	y = 0;
	while (game_struct->minimap.map[y])
	{
		printf("%s", game_struct->minimap.map[y]);
		y++;
	}
}

void	player_current_grid_pos(t_minimap *map)
{
	printf("Player is in grid cell: (%d, %d)\n",
			map->player_grid_x, map->player_grid_y);
}

void	draw_degub_green_line_direction(t_struct *game_struct)
{
	int	center_x;
	int	center_y;
	int i;
	double	radians;
	int	line_length;
	int	px;
	int	py;
	
	center_x = game_struct->player.pos.x * MINIMAP_TILE_SIZE;
	center_y = game_struct->player.pos.y * MINIMAP_TILE_SIZE;
	i = 0;
	radians = game_struct->player.radians;
	line_length = 100;
	i = -1;
	while (++i < line_length)
	{
		px = center_x + MINIMAP_PLAYER_SIZE / 2 + cos(radians) * i;
		py = center_y + MINIMAP_PLAYER_SIZE / 2 + sin(radians) * i;
		if (px >= 0 && px < (game_struct->minimap.map_width
				* MINIMAP_TILE_SIZE) &&	py >= 0 && py
				< (game_struct->minimap.map_height * MINIMAP_TILE_SIZE))
		{
			mlx_put_pixel(game_struct->minimap_img, px, py, GREEN);
		}
	}
}