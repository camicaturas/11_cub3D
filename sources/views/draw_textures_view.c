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

void	draw_wall_strip(t_struct *game_data, int top_pixel, int bottom_pixel,
	double texture_x, double texture_y,	double scale_factor,
		mlx_texture_t *texture,	uint32_t *texture_pixels)
{
	uint32_t	color;
	int			tex_x;
	int			tex_y;

	if (texture_y < 0)
		texture_y = 0;
	while (top_pixel < bottom_pixel)
	{
		tex_x = (int)texture_x;
		tex_y = (int)texture_y;
		if (tex_x >= 0 && tex_x < (int)texture->width
			&& tex_y >= 0 && tex_y < (int)texture->height)
		{
			color = texture_pixels[tex_y * texture->width + tex_x];
			draw_game_pixel(game_data, game_data->ray->ray_index,
				top_pixel, swap_bytes_order(color));
		}
		texture_y += scale_factor;
		top_pixel++;
	}
}

void	draw_textured_wall(t_struct *game, double wall_height,
		int top_pixel, int bottom_pixel)
{
	double			scale_factor;
	double			texture_x;
	double			start_texture_y;
	mlx_texture_t	*texture;
	uint32_t		*pixels;

	texture = get_texture(game, game->ray->is_active);
	if (!texture)
		return ;
	pixels = get_texture_pixels(texture);
	if (!pixels)
		return ;
	scale_factor = (double)texture->height / wall_height;
	texture_x = get_texture_x_offset(game, texture);
	start_texture_y = calculate_texture_y_offset(
			wall_height, top_pixel) * scale_factor;
	draw_wall_strip(game, top_pixel, bottom_pixel,
		texture_x, start_texture_y, scale_factor, texture, pixels);
}

int	calc_wall_bounds(double distance, double *top, double *bottom, int fov_rad)
{
	double	wall_height;

	wall_height = (TILE_SIZE / distance)
		* ((WINDOW_WIDTH / 2.0) / tan(fov_rad / 2.0));
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
	double	distance;
	double	top_pixel;
	double	bottom_pixel;
	double	wall_height;

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
