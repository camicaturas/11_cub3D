/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_controller.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/07/31 15:19:51 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static	void	update_ray_distance(t_struct *game_struct,
	double hor_distance, double ver_distance)
{
	if (ver_distance <= hor_distance)
	{
		game_struct->ray->distance = ver_distance;
	}
	else
	{
		game_struct->ray->distance = hor_distance;
		game_struct->ray->is_active = 1;
	}
}

static	void	process_single_ray(t_struct *game_struct,
	double *hor_distance, double *ver_distance)
{
	double	angle;

	game_struct->ray->is_active = 0;
	angle = normalize_angle(game_struct->ray->ray_angle);
	*hor_distance = calculate_horizontal_ray_hit(angle, game_struct);
	*ver_distance = calculate_vertical_ray_hit(angle, game_struct);
}

void	raycast_controller(t_struct *game_struct)
{
	int		column;
	double	hor_distance;
	double	ver_distance;

	column = 0;
	game_struct->ray->ray_angle = game_struct->player.radians
		- (game_struct->player.fov_in_radians / 2);
	while (column < WINDOW_WIDTH)
	{
		process_single_ray(game_struct, &hor_distance, &ver_distance);
		update_ray_distance(game_struct, hor_distance, ver_distance);
		draw_wall_column(column, game_struct);
		game_struct->ray->ray_angle +=
			(game_struct->player.fov_in_radians / WINDOW_WIDTH);
		column++;
	}
}

/*
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
		game_struct->ray->ray_angle += 
			(game_struct->player.fov_in_radians / WINDOW_WIDTH);
		column++;
	}
}
*/