/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_extra_textures_view.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/07/31 15:19:09 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	draw_roof(t_struct *game, int top_pixel, int ray)
{
	int	y;

	y = 0;
	while (y < top_pixel)
	{
		draw_game_pixel(game, ray, y, game->texdata.hex_roof);
		y++;
	}
}

void	draw_floor(t_struct *game, int bottom_pixel, int ray)
{
	int	y;

	y = bottom_pixel;
	while (y < WINDOW_HEIGHT)
	{
		draw_game_pixel(game, ray, y, game->texdata.hex_floor);
		y++;
	}
}

double	calculate_texture_y_offset(double wall_height, int top_pixel)
{
	return (top_pixel - (WINDOW_HEIGHT / 2.0) + (wall_height / 2.0));
}

uint32_t	*get_texture_pixels(mlx_texture_t *texture)
{
	if (!texture || !texture->pixels)
		return (NULL);
	return ((uint32_t *)texture->pixels);
}

double	get_corrected_distance(t_struct *game_struct)
{
	double	angle_diff;
	double	corrected;

	angle_diff = normalize_angle(
			game_struct->ray->ray_angle - game_struct->player.radians);
	corrected = game_struct->ray->distance * cos(angle_diff);
	if (corrected < 0.0001)
		corrected = 0.0001;
	return (corrected);
}
