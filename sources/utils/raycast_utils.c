/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/05/26 13:54:53 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"
 
static void	dda_draw_line(t_struct *game, int start_x,
		int start_y, int end_x, int end_y)
{
	int		dx = end_x - start_x;
	int		dy = end_y - start_y;
	int		steps = (int)fmax(fabs((double)dx), fabs((double)dy));
	double	x, y, x_inc, y_inc;
	int		i = 0;

	if (steps == 0)
		return;

	x_inc = dx / (double)steps;
	y_inc = dy / (double)steps;
	x = start_x;
	y = start_y;
	while (i < steps)
	{
		if (x >= 0 && y >= 0 &&
			x < game->minimap.map_width * MINIMAP_TILE_SIZE &&
			y < game->minimap.map_height * MINIMAP_TILE_SIZE)
		{
			mlx_put_pixel(game->minimap_img, (int)x, (int)y, GREEN);
		}
		x += x_inc;
		y += y_inc;
		i++;
	}
}

void	draw_rays_on_minimap(t_struct *game, t_ray ray)
{
	int	start_px = game->player.pos.x * MINIMAP_TILE_SIZE;
	int	start_py = game->player.pos.y * MINIMAP_TILE_SIZE;
	int	end_px = ray.hit_x * MINIMAP_TILE_SIZE;
	int	end_py = ray.hit_y * MINIMAP_TILE_SIZE;

	dda_draw_line(game, start_px, start_py, end_px, end_py);
}