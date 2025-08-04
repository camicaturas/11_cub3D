/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/07/31 15:18:38 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

uint32_t	swap_bytes_order(uint32_t val)
{
	return ((val >> 24) & 0x000000FF) |
			((val >> 8)  & 0x0000FF00) |
			((val << 8)  & 0x00FF0000) |
			((val << 24) & 0xFF000000);
}

void	draw_game_pixel(t_struct *game_struct, int x, int y, int color)
{
	if (!game_struct || !game_struct->main_img)
		return ;
	if (x >= WINDOW_WIDTH || y >= WINDOW_HEIGHT || x < 0 || y < 0)
		return ;
	mlx_put_pixel(game_struct->main_img, x, y, color);
}

int	detect_hit_wall(t_struct *game_struct, float world_x, float world_y)
{
	int		map_x;
	int		map_y;
	char	*map_row;

	if (world_x < 0 || world_y < 0)
		return (0);
	map_x = (int)(world_x / TILE_SIZE);
	map_y = (int)(world_y / TILE_SIZE);
	if (map_y >= game_struct->minimap.map_height || 
		map_x >= game_struct->minimap.map_width)
		return (0);
	map_row = game_struct->minimap.map[map_y];
	if (!map_row || map_x >= (int)ft_strlen(map_row))
		return (0);
	return (map_row[map_x] != '1');
}

void	draw_wall_plain_colors(t_struct *game_struct, int t_pix, int b_pix)
{
	int	color;

	if (game_struct->ray->is_active == 1)
	{
		if (game_struct->ray->ray_angle > 0
			&& game_struct->ray->ray_angle < PI)
			color = BLUE;
		else
			color = CYAN;
	}
	else
	{
		if (game_struct->ray->ray_angle > PI/2
			&& game_struct->ray->ray_angle < 3 * (PI / 2))
			color = YELLOW;
		else
			color = MAGENTA;
	}
	while (t_pix < b_pix)
	{
		draw_game_pixel(game_struct,
			game_struct->ray->ray_index, t_pix, color);
		t_pix++;
	}
}
