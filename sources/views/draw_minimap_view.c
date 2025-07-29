/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/07/08 15:21:29 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	draw_direction_line(t_struct *game_struct)
{
	int		center_x = game_struct->player.pos.x + MINIMAP_PLAYER_SIZE / 2;
	int		center_y = game_struct->player.pos.y + MINIMAP_PLAYER_SIZE / 2;
	double	radians = game_struct->player.radians;
	int		line_length = 25;
	int		i = 0;

	while (i < line_length)
	{
		int px = center_x + (int)(cos(radians) * i);
		int py = center_y + (int)(sin(radians) * i);

		if (px < 0 || px >= game_struct->minimap.map_width
			 * MINIMAP_TILE_SIZE ||	py < 0 || py >= 
			 game_struct->minimap.map_height * MINIMAP_TILE_SIZE)
			break;

		mlx_put_pixel(game_struct->minimap_img, px, py, COLOR_PLAYER);
		i++;
	}
}

void	draw_tile(mlx_image_t *img, int x, int y, uint32_t color)
{
	int	i = 0;
	while (i < MINIMAP_TILE_SIZE)
	{
		int	j = 0;
		while (j < MINIMAP_TILE_SIZE)
		{
			//You draw pixels to [mlx_image_t	*img] with mlx_put_pixel(img, x, y, color);
			mlx_put_pixel(img, x * MINIMAP_TILE_SIZE + i, y * MINIMAP_TILE_SIZE + j, color);
			j++;
		}
		i++;
	}
}

void	draw_player_square(t_struct *game_struct, mlx_image_t *img)
{
	int	i = 0;
	while (i < MINIMAP_PLAYER_SIZE)
	{
		int	j = 0;
		while (j < MINIMAP_PLAYER_SIZE)
		{
			int	px = game_struct->player.pos.x + i;
			int	py = game_struct->player.pos.y + j;

			if (px >= 0 && px < (game_struct->minimap.map_width * MINIMAP_TILE_SIZE) &&
				py >= 0 && py < (game_struct->minimap.map_height * MINIMAP_TILE_SIZE))
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
	if(SHOW_CHARACTER == 1)
		draw_player_square(game_struct, img);
	if(SHOW_DIRECTION_LINE == 1)
		draw_direction_line(game_struct);
}

void	draw_map(mlx_image_t *img, t_struct *game_struct)
{
	int	y = 0;
	while (game_struct->minimap.map[y])
	{
		int	x = 0;
		while (game_struct->minimap.map[y][x])
		{
			if (game_struct->minimap.map[y][x] == '1')
				draw_tile(img, x, y, COLOR_WALL);
			else if (game_struct->minimap.map[y][x] == 'I')
			{
				if(SHOW_ITEMS_IN_MAP == 1)
					draw_tile(img, x, y, COLOR_ITEM);
				else
					draw_tile(img, x, y, COLOR_FLOOR);
			}
			else if (game_struct->minimap.map[y][x] == '0')
				draw_tile(img, x, y, COLOR_FLOOR);
			x++;
		}
		y++;
	}
	draw_map_with_config(img,game_struct);
}
