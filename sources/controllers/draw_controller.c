/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_controller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/07/31 15:19:44 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	ray_facing_up_or_left(char axis, float angle)
{
	if (axis == 'y')
	{
		if (angle > (PI / 2) && angle < (3 * PI) / 2)
			return (1);
	}
	else if (axis == 'x')
	{
		if (angle > 0 && angle < PI)
			return (1);
	}
	return (0);
}

int	ray_intersection(float *coord, int is_horizontal, float *step, float angle)
{
	if (is_horizontal)
	{
		if (angle > 0 && angle < PI)
		{
			*coord += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > PI / 2 && angle < 3 * PI / 2))
		{
			*coord += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

void	init_horizontal_intersection(float angle, t_struct *game_struct, 
	float *intersect_x, float *intersect_y, float *step_x, 
		float *step_y, int *pixel_offset)
{
	*step_y = TILE_SIZE;
	*step_x = TILE_SIZE / tan(angle);
	*intersect_y = floor(game_struct->player.pos.y / TILE_SIZE) * TILE_SIZE;
	*pixel_offset = ray_intersection(intersect_y, 1, step_y, angle);
	*intersect_x = game_struct->player.pos.x + (*intersect_y - game_struct->player.pos.y) / tan(angle);
	if ((ray_facing_up_or_left('y', angle) && *step_x > 0) ||
		(!ray_facing_up_or_left('y', angle) && *step_x < 0))
		*step_x *= -1;
}

float	calculate_horizontal_ray_hit(float angle, t_struct *game_struct)
{
	float	intersect_x, intersect_y;
	float	step_x, step_y;
	int		pixel_offset;

	init_horizontal_intersection(angle, game_struct,
		&intersect_x, &intersect_y, &step_x, &step_y, &pixel_offset);
	while (detect_hit_wall(game_struct, 
		intersect_x, intersect_y - pixel_offset))
	{
		intersect_x += step_x;
		intersect_y += step_y;
	}
	game_struct->ray->intersect_horz_x = intersect_x;
	game_struct->ray->intersect_horz_y = intersect_y;
	return sqrt(pow(intersect_x - game_struct->player.pos.x, 2) +
				pow(intersect_y - game_struct->player.pos.y, 2));
}

void	init_vertical_intersection(float angle, t_struct *game_struct,
	float *intersect_x, float *intersect_y, 
		float *step_x, float *step_y, int *pixel_offset)
{
	*step_x = TILE_SIZE;
	*step_y = TILE_SIZE * tan(angle);
	*intersect_x = floor(game_struct->player.pos.x / TILE_SIZE) * TILE_SIZE;
	*pixel_offset = ray_intersection(intersect_x, 0, step_x, angle);
	*intersect_y = game_struct->player.pos.y +
		(*intersect_x - game_struct->player.pos.x) * tan(angle);
	if ((ray_facing_up_or_left('x', angle) && *step_y < 0) ||
		(!ray_facing_up_or_left('x', angle) && *step_y > 0))
		*step_y *= -1;
}

float	calculate_vertical_ray_hit(float angle, t_struct *game_struct)
{
	float	intersect_x, intersect_y;
	float	step_x, step_y;
	int		pixel_offset;

	init_vertical_intersection(angle, game_struct,
		&intersect_x, &intersect_y, &step_x, &step_y, &pixel_offset);
	while (detect_hit_wall(game_struct, 
		intersect_x - pixel_offset, intersect_y))
	{
		intersect_x += step_x;
		intersect_y += step_y;
	}
	game_struct->ray->intersect_vert_x = intersect_x;
	game_struct->ray->intersect_vert_y = intersect_y;
	return sqrt(pow(intersect_x - game_struct->player.pos.x, 2) +
				pow(intersect_y - game_struct->player.pos.y, 2));
}

void	draw_controller(t_struct *game_struct)
{
	draw_new_image(game_struct);
	raycast_controller(game_struct);
	if(SHOW_MAP == 1)
		draw_map(game_struct->minimap_img, game_struct);
	if(SHOW_FOV == 1)
		draw_all_green_rays(game_struct);
	if(SHOW_MAP_GRID == 1)
		draw_minimap_grid(game_struct);
}