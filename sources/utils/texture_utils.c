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

uint32_t	rgb_to_hex(char *rgb_str)
{
	int			r, g, b;
	char		*end;

	// Parse red
	r = strtol(rgb_str, &end, 10);
	if (*end != ',')
		return (0x0); // invalid format

	// Parse green
	g = strtol(end + 1, &end, 10);
	if (*end != ',')
		return (0x0); // invalid format

	// Parse blue
	b = strtol(end + 1, NULL, 10);

	// Clamp values and convert to hex
	return ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
}

//FIXED!
mlx_texture_t	*get_horizontal_texture(t_struct *game_struct)
{
	if (game_struct->ray->ray_angle > PI / 2 &&
		game_struct->ray->ray_angle < 3 * (PI / 2))
	{
		if (!game_struct->texture.west)
		{
			ft_putstr_fd("Error: West texture is NULL\n", 2);
			exit(1);
		}
		return (game_struct->texture.west);
	}
	else
	{
		if (!game_struct->texture.east)
		{
			ft_putstr_fd("Error: East texture is NULL\n", 2);
			exit(1);
		}
		return (game_struct->texture.east);
	}
}

//FIXED!
mlx_texture_t	*get_vertical_texture(t_struct *game_struct)
{
	if (game_struct->ray->ray_angle > 0 && game_struct->ray->ray_angle < PI)
	{
		if (!game_struct->texture.south)
		{
			ft_putstr_fd("Error: South texture is NULL\n", 2);
			exit(1);
		}
		return (game_struct->texture.south);
	}
	else
	{
		if (!game_struct->texture.north)
		{
			ft_putstr_fd("Error: North texture is NULL\n", 2);
			exit(1);
		}
		return (game_struct->texture.north);
	}
}

//FIXED!
mlx_texture_t	*get_texture(t_struct *game_struct, int hit_type)
{
	if (!game_struct->ray)
	{
		ft_putstr_fd("Error: game_struct->ray is NULL\n", 2);
		exit(1);
	}
	game_struct->ray->ray_angle = normalize_angle(game_struct->ray->ray_angle);
	if (hit_type == 0)
		return get_horizontal_texture(game_struct);
	else
		return get_vertical_texture(game_struct);
}

//FIXED!
//calculates the X offset into a wall texture for rendering a vertical strip in raycasting
//Calcula el desplazamiento X en una textura de pared para renderizar una franja vertical en Raycasting.
double	get_texture_x_offset(t_struct *game_struct, mlx_texture_t *texture)
{
	double	texture_x_offset;

	if (game_struct->ray->is_active != 1)
		texture_x_offset = (int)fmodf((game_struct->ray->intersect_vert_y *
			(texture->width / TILE_SIZE)), texture->width);
	else
		texture_x_offset = (int)fmodf((game_struct->ray->intersect_horz_x *
			(texture->width / TILE_SIZE)), texture->width);	
	return (texture_x_offset);
}