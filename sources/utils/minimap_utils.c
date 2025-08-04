/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/07/31 15:18:53 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static	void	draw_vertical_grid_lines(t_struct *game_struct,
		int map_width, int map_height, int tile_size)
{
	int x;
	int y;

	x = 0;
	while (x < map_width)
	{
		y = 0;
		while (y < map_height * tile_size)
		{
			mlx_put_pixel(game_struct->minimap_img,
				x * tile_size, y, DARK_GRAY);
			y++;
		}
		x++;
	}
}

static	void	draw_horizontal_grid_lines(t_struct *game_struct,
		int map_width, int map_height, int tile_size)
{
	int x;
	int y;

	y = 0;
	while (y < map_height)
	{
		x = 0;
		while (x < map_width * tile_size)
		{
			mlx_put_pixel(game_struct->minimap_img,
				x, y * tile_size, DARK_GRAY);
			x++;
		}
		y++;
	}
}

void	draw_minimap_grid(t_struct *game_struct)
{
	int map_width;
	int map_height;
	int tile_size;

	map_width = game_struct->minimap.map_width;
	map_height = game_struct->minimap.map_height;
	tile_size = MINIMAP_TILE_SIZE;
	draw_vertical_grid_lines(game_struct, map_width, map_height, tile_size);
	draw_horizontal_grid_lines(game_struct, map_width, map_height, tile_size);
}
