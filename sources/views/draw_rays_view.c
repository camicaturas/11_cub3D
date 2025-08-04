/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures_view.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/07/31 15:19:12 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static int	check_wall_or_bounds(t_struct *game_struct, int map_x, int map_y)
{
	if (map_x < 0 || map_y < 0)
		return (1);
	if (map_x >= game_struct->minimap.map_width ||
		map_y >= game_struct->minimap.map_height)
		return (1);
	if (game_struct->minimap.map[map_y][map_x] == '1')
		return (1);
	return (0);
}

static void	draw_ray_pixel(t_struct *game_struct, int px, int py)
{
	if (px >= 0 && py >= 0 &&
		px < game_struct->minimap.map_width * MINIMAP_TILE_SIZE &&
		py < game_struct->minimap.map_height * MINIMAP_TILE_SIZE)
	{
		mlx_put_pixel(game_struct->minimap_img, px, py, GREEN);
	}
}

static	void	draw_ray_loop(t_struct *game_struct,
	double ray_x, double ray_y, double dx, double dy)
{
	double	distance;
	double	step_size;
	double	max_distance;
	int		map_x;
	int		map_y;
	int		px;
	int		py;

	distance = 0.0;
	step_size = 0.05;
	max_distance = 10.0;
	while (distance < max_distance)
	{
		ray_x += dx;
		ray_y += dy;
		distance += step_size;
		map_x = (int)ray_x;
		map_y = (int)ray_y;
		if (check_wall_or_bounds(game_struct, map_x, map_y))
			break ;
		px = ray_x * MINIMAP_TILE_SIZE;
		py = ray_y * MINIMAP_TILE_SIZE;
		draw_ray_pixel(game_struct, px, py);
	}
}

void	draw_green_ray(t_struct *game_struct, double angle)
{
	double	ray_x;
	double	ray_y;
	double	step_size;
	double	dx;
	double	dy;

	step_size = 0.05;
	ray_x = game_struct->player.pos.x / MINIMAP_TILE_SIZE;
	ray_y = game_struct->player.pos.y / MINIMAP_TILE_SIZE;
	dx = cos(angle) * step_size;
	dy = sin(angle) * step_size;
	draw_ray_loop(game_struct, ray_x, ray_y, dx, dy);
}

/*
void	draw_green_ray(t_struct *game_struct, double angle)
{
	double	ray_x;
	double	ray_y;
	double	step_size;
	double	max_distance;
	double	dx;
	double	dy;
	double	distance;
	int	map_x;
	int	map_y;
	int	px;
	int	py;

	distance = 0.0;
	max_distance = 10.0;
	ray_x = game_struct->player.pos.x / MINIMAP_TILE_SIZE;
	ray_y = game_struct->player.pos.y / MINIMAP_TILE_SIZE;
	dx = cos(angle) * step_size;
	dy = sin(angle) * step_size;
	while (distance < max_distance)
	{
		ray_x += dx;
		ray_y += dy;
		distance += step_size;
		map_x = (int)ray_x;
		map_y = (int)ray_y;
		if (map_x < 0 || map_y < 0 ||
			map_x >= game_struct->minimap.map_width ||
			map_y >= game_struct->minimap.map_height)
			break ;
		if (game_struct->minimap.map[map_y][map_x] == '1')
			break ;
		px = ray_x * MINIMAP_TILE_SIZE;
		py = ray_y * MINIMAP_TILE_SIZE;
		if (px >= 0 && py >= 0 &&
			px < (game_struct->minimap.map_width * MINIMAP_TILE_SIZE) &&
			py < (game_struct->minimap.map_height * MINIMAP_TILE_SIZE))
		{	
			mlx_put_pixel(game_struct->minimap_img, px, py, GREEN);
		}
	}
}
*/
