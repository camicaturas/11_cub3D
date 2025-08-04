/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/07/31 15:18:48 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static	void	dda_draw_loop(t_struct *game, int steps,
		double x, double y, double x_inc, double y_inc)
{
	int	i;

	i = 0;
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

static	void	dda_draw_line(t_struct *game, int start_x,
		int start_y, int end_x, int end_y)
{
	int		dx;
	int		dy;
	int		steps;
	double	x_inc;
	double	y_inc;

	dx = end_x - start_x;
	dy = end_y - start_y;
	steps = (int)fmax(fabs((double)dx), fabs((double)dy));
	if (steps == 0)
		return ;
	x_inc = dx / (double)steps;
	y_inc = dy / (double)steps;
	dda_draw_loop(game, steps, start_x, start_y, x_inc, y_inc);
}

/*
static void	dda_draw_line(t_struct *game, int start_x,
		int start_y, int end_x, int end_y)
{
	int		dx;
	int		dy;
	int		steps;
	double	x;
	double	y;
	double	x_inc;
	double	y_inc;
	int		i;

	dx = end_x - start_x;
	dy = end_y - start_y;
	steps = (int)fmax(fabs((double)dx), fabs((double)dy));
	i = 0;
	if (steps == 0)
		return ;
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
*/
void	draw_all_green_rays(t_struct *game_struct)
{
	double	player_angle;
	double	fov;
	int		num_rays;
	double	angle_step;
	double	start_angle;
	double	ray_angle;
	int		i;

	player_angle = game_struct->player.radians;
	fov = 60 * (M_PI / 180.0);
	num_rays = 100;
	angle_step = fov / num_rays;
	start_angle = player_angle - (fov / 2);
	i = 0;
	while (i < num_rays)
	{
		ray_angle = start_angle + i * angle_step;
		draw_green_ray(game_struct, ray_angle);
		i++;
	}
}

void	draw_rays_on_minimap(t_struct *game, t_ray ray)
{
	int	start_px;
	int	start_py;
	int	end_px;
	int	end_py;

	start_px = game->player.pos.x * MINIMAP_TILE_SIZE;
	start_py = game->player.pos.y * MINIMAP_TILE_SIZE;
	end_px = ray.hit_x * MINIMAP_TILE_SIZE;
	end_py = ray.hit_y * MINIMAP_TILE_SIZE;
	dda_draw_line(game, start_px, start_py, end_px, end_py);
}
