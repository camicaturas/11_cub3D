/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_controller.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/07/08 15:22:20 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

//basic raycaster (map collision + line drawing).
void	draw_green_ray(t_struct *game_struct, double angle)
{
	double	ray_x = game_struct->player.pos.x / MINIMAP_TILE_SIZE;;
	double	ray_y = game_struct->player.pos.y / MINIMAP_TILE_SIZE;;
	double	step_size = 0.05;
	double	max_distance = 10.0; // in map units, not pixels

	double	dx = cos(angle) * step_size;
	double	dy = sin(angle) * step_size;

	double	distance = 0.0;

	while (distance < max_distance)
	{
		ray_x += dx;
		ray_y += dy;
		distance += step_size;

		int	map_x = (int)ray_x;
		int	map_y = (int)ray_y;

		// Bounds check
		if (map_x < 0 || map_y < 0 ||
			map_x >= game_struct->minimap.map_width ||
			map_y >= game_struct->minimap.map_height)
			break;

		// Stop on wall
		if (game_struct->minimap.map[map_y][map_x] == '1')
			break;

		// Draw pixel
		int	px = ray_x * MINIMAP_TILE_SIZE;
		int	py = ray_y * MINIMAP_TILE_SIZE;

		if (px >= 0 && py >= 0 &&
			px < (game_struct->minimap.map_width * MINIMAP_TILE_SIZE) &&
			py < (game_struct->minimap.map_height * MINIMAP_TILE_SIZE))
		{	
			mlx_put_pixel(game_struct->minimap_img, px, py, GREEN);
		}
	}
}

//draws a wide green view in the minimap
void	draw_all_green_rays(t_struct *game_struct)
{
	double	player_angle = game_struct->player.radians;
	double	fov = 60 * (M_PI / 180.0); // 60 degrees in radians
	int		num_rays = 100; // number of rays to cast
	double	angle_step = fov / num_rays;

	double	start_angle = player_angle - (fov / 2);

	for (int i = 0; i < num_rays; i++)
	{
		double ray_angle = start_angle + i * angle_step;
		draw_green_ray(game_struct, ray_angle);
	}
}

// FIXED
void	raycast_controller(t_struct *game_struct)
{
	int		column;
	double	hor_distance;
	double	ver_distance;

	column = 0;
	game_struct->ray->ray_angle = game_struct->player.radians -
		(game_struct->player.fov_in_radians / 2);
	while (column < WINDOW_WIDTH)
	{
		game_struct->ray->is_active = 0;
		hor_distance = calculate_horizontal_ray_hit(
				normalize_angle(game_struct->ray->ray_angle), game_struct);
		ver_distance = calculate_vertical_ray_hit(
				normalize_angle(game_struct->ray->ray_angle), game_struct);
		if (ver_distance <= hor_distance)
			game_struct->ray->distance = ver_distance;
		else
		{
			game_struct->ray->distance = hor_distance;
			game_struct->ray->is_active = 1;
		}
		draw_wall_column(column, game_struct);
		//game_struct->zbuffer[column] = game_struct->ray->distance; // FOR ITEMS
		game_struct->ray->ray_angle += (game_struct->player.fov_in_radians / WINDOW_WIDTH);
		column++;
	}
}