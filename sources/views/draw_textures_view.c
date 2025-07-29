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

void	draw_roof(t_struct *game, int top_pixel, int ray)
{
	int y = 0;
	while (y < top_pixel)
	{
		draw_game_pixel(game, ray, y, game->texdata.hex_roof);
		y++;
	}
}

void	draw_floor(t_struct *game, int bottom_pixel, int ray)
{
	int y = bottom_pixel;
	while (y < WINDOW_HEIGHT)
	{
		draw_game_pixel(game, ray, y, game->texdata.hex_floor);
		y++;
	}
}

// FIXED
//renders a vertical slice of a textured wall onto the screen for a raycasting-based 3D engine
void draw_wall_strip(t_struct *game_data, int top_pixel, int bottom_pixel,
	double texture_x, double texture_y,	double scale_factor,
		mlx_texture_t *texture,	uint32_t *texture_pixels)
{
	if (texture_y < 0)
		texture_y = 0;
	while (top_pixel < bottom_pixel)
	{
		int tex_x = (int)texture_x;
		int tex_y = (int)texture_y;

		if (tex_x >= 0 && tex_x < (int)texture->width &&
			tex_y >= 0 && tex_y < (int)texture->height)
		{
			uint32_t color = texture_pixels[tex_y * texture->width + tex_x];
			draw_game_pixel(game_data, game_data->ray->ray_index, top_pixel, swap_bytes_order(color));
		}
		texture_y += scale_factor;
		top_pixel++;
	}
}



double calculate_texture_y_offset(double wall_height, int top_pixel)
{
	return (top_pixel - (WINDOW_HEIGHT / 2.0) + (wall_height / 2.0));
}

uint32_t *get_texture_pixels(mlx_texture_t *texture)
{
	if (!texture || !texture->pixels)
		return NULL;
	return (uint32_t *)texture->pixels;
}

//it draws a vertical wall slice using raycasting, texture mapping, and vertical scaling. 
void draw_textured_wall(t_struct *game, double wall_height, int top_pixel, int bottom_pixel)
{
	mlx_texture_t *texture = get_texture(game, game->ray->is_active);
	if (!texture)
		return;

	uint32_t *pixels = get_texture_pixels(texture);
	if (!pixels)
		return;

	double scale_factor = (double)texture->height / wall_height;
	double texture_x = get_texture_x_offset(game, texture);
	double start_texture_y = calculate_texture_y_offset(wall_height, top_pixel) * scale_factor;

	draw_wall_strip(game, top_pixel, bottom_pixel,
		texture_x, start_texture_y, scale_factor, texture, pixels);
}


/*
void draw_textured_wall(t_struct *game_struct, double wall_height, int top_pixel, int bottom_pixel)
{
	double texture_x;
	double texture_y;
	uint32_t *texture_pixels;
	double scale_factor;
	mlx_texture_t *texture;

	texture = get_texture(game_struct, game_struct->ray->is_active);
	texture_pixels = (uint32_t *)texture->pixels;
	scale_factor = (double)texture->height / wall_height;
	texture_x = get_texture_x_offset(game_struct, texture);
	texture_y = (top_pixel - (WINDOW_HEIGHT / 2.0) +
		(wall_height / 2.0)) * scale_factor;
	draw_wall_strip(game_struct, top_pixel, bottom_pixel,
		 texture_x, texture_y, scale_factor, texture, texture_pixels);
}
*/

double	get_corrected_distance(t_struct *game_struct)
{
	double angle_diff;
	double corrected;

	angle_diff = normalize_angle(
		game_struct->ray->ray_angle - game_struct->player.radians);
	corrected = game_struct->ray->distance * cos(angle_diff);
	if (corrected < 0.0001)
		corrected = 0.0001;
	return (corrected);
}

int	calc_wall_bounds(double distance, double *top, double *bottom, int fov_rad)
{
	double wall_height;

	wall_height = (TILE_SIZE / distance) *
		((WINDOW_WIDTH / 2.0) / tan(fov_rad / 2.0));
	*bottom = (WINDOW_HEIGHT / 2.0) + (wall_height / 2.0);
	*top = (WINDOW_HEIGHT / 2.0) - (wall_height / 2.0);
	if (*bottom > WINDOW_HEIGHT)
		*bottom = WINDOW_HEIGHT;
	if (*top < 0)
		*top = 0;
	return (wall_height);
}

void	draw_wall_column(int ray, t_struct *game_struct)
{
	double distance;
	double top_pixel;
	double bottom_pixel;
	double wall_height;

	distance = get_corrected_distance(game_struct);
	wall_height = calc_wall_bounds(distance, &top_pixel, &bottom_pixel,
		 game_struct->player.fov_in_radians);
	game_struct->ray->ray_index = ray;
	if (TEXTURED_WALLS == 0)
		draw_wall_plain_colors(game_struct, top_pixel, bottom_pixel);
	else
		draw_textured_wall(game_struct, wall_height, top_pixel, bottom_pixel);
	draw_roof(game_struct, top_pixel, ray);
	draw_floor(game_struct, bottom_pixel, ray);
}