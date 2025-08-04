/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_view.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/07/31 14:33:46 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	draw_direction_line(t_struct *game_struct)
{
	int		center_x;
	int		center_y;
	double	radians;
	int		line_length;
	int		i;
	int		px;
	int		py;

	center_x = game_struct->player.pos.x + MINIMAP_PLAYER_SIZE / 2;
	center_y = game_struct->player.pos.y + MINIMAP_PLAYER_SIZE / 2;
	radians = game_struct->player.radians;
	line_length = 25;
	i = 0;
	while (i < line_length)
	{
		px = center_x + (int)(cos(radians) * i);
		py = center_y + (int)(sin(radians) * i);
		if (px < 0 || px >= game_struct->minimap.map_width
			 * MINIMAP_TILE_SIZE ||	py < 0 || py >=
			 game_struct->minimap.map_height * MINIMAP_TILE_SIZE)
			break ;
		mlx_put_pixel(game_struct->minimap_img, px, py, COLOR_PLAYER);
		i++;
	}
}

void	draw_tile(mlx_image_t *img, int x, int y, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_TILE_SIZE)
	{
		j = 0;
		while (j < MINIMAP_TILE_SIZE)
		{
			mlx_put_pixel(img, x * MINIMAP_TILE_SIZE
				+ i, y * MINIMAP_TILE_SIZE + j, color);
			j++;
		}
		i++;
	}
}

void	draw_player_square(t_struct *game_struct, mlx_image_t *img)
{
	int	i;
	int	j;
	int	px;
	int	py;

	i = 0;
	while (i < MINIMAP_PLAYER_SIZE)
	{
		j = 0;
		while (j < MINIMAP_PLAYER_SIZE)
		{
			px = game_struct->player.pos.x + i;
			py = game_struct->player.pos.y + j;
			if (px >= 0 && px < (game_struct->minimap.map_width
					* MINIMAP_TILE_SIZE) && py >= 0 && py < (
					game_struct->minimap.map_height * MINIMAP_TILE_SIZE))
			{
				mlx_put_pixel(img, px, py, COLOR_PLAYER);
			}
			j++;
		}
		i++;
	}
}

void	draw_map_with_config(mlx_image_t *img, t_struct *game_struct)
{
	if (SHOW_CHARACTER == 1)
		draw_player_square(game_struct, img);
	if (SHOW_DIRECTION_LINE == 1)
		draw_direction_line(game_struct);
}

void	draw_map(mlx_image_t *img, t_struct *game_struct)
{
	int	y;
	int	x;

	y = 0;
	while (game_struct->minimap.map[y])
	{
		x = 0;
		while (game_struct->minimap.map[y][x])
		{
			if (game_struct->minimap.map[y][x] == '1')
				draw_tile(img, x, y, COLOR_WALL);
			else if (game_struct->minimap.map[y][x] == '0')
				draw_tile(img, x, y, COLOR_FLOOR);
			x++;
		}
		y++;
	}
	draw_map_with_config(img, game_struct);
}
