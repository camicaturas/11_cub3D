/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_controller.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:21:22 by ohosnedl          #+#    #+#             */
/*   Updated: 2025/07/31 15:19:50 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	validate_textures(t_texture_data *texts, t_struct *game_struct)
{
	int	rgb[3];

	if (!texts->no || !texts->so || !texts->we || !texts->ea)
	{
		error_controller(game_struct, TEXTURE_MISSING);
		return (1);
	}
	if (!texts->floor || !texts->roof)
	{
		error_controller(game_struct, COLOR_MISSING);
		return (1);
	}
	if (verify_file_integrity(game_struct, texts->we, "texture") == 0
		|| verify_file_integrity(game_struct, texts->so, "texture") == 0
		|| verify_file_integrity(game_struct, texts->no, "texture") == 0
		|| verify_file_integrity(game_struct, texts->ea, "texture") == 0)
		return (1);
	if (parse_rgb(texts->roof, rgb) == 1 || parse_rgb(texts->floor, rgb) == 1)
		return (1);
	texts->hex_floor = rgb_to_hex(texts->floor);
	texts->hex_roof = rgb_to_hex(texts->roof);
	return (0);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

bool	parse_rgb(char *str, int *rgb)
{
	char	**split;
	int		i;

	split = ft_split(str, ',');
	if (!split)
	{
		ft_putstr_fd("RGB parsing failed\n", 2);
		return (1);
	}
	i = 0;
	while (i < 3)
	{
		rgb[i] = ft_atoi(split[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			ft_putstr_fd("RGB value out of range\n", 2);
			return (1);
		}
		i++;
	}
	free_split(split);
	return (0);
}

void	load_textures(t_struct *game_struct)
{
	int	rgb[3];

	game_struct->texture.north = mlx_load_png(game_struct->texdata.no);
	game_struct->texture.south = mlx_load_png(game_struct->texdata.so);
	game_struct->texture.east = mlx_load_png(game_struct->texdata.ea);
	game_struct->texture.west = mlx_load_png(game_struct->texdata.we);
	if (!game_struct->texture.north || !game_struct->texture.south
		|| !game_struct->texture.east || !game_struct->texture.west)
		error_controller(game_struct, TEXTURE_LOAD_FAIL);
	if (parse_rgb(game_struct->texdata.floor, rgb) == 1)
		error_controller(game_struct, FLOOR_COLOR_INVALID);
	game_struct->texture.color_floor = get_rgba(rgb[0], rgb[1], rgb[2], 255);
	if (parse_rgb(game_struct->texdata.roof, rgb) == 1)
		error_controller(game_struct, CEILING_COLOR_INVALID);
	game_struct->texture.color_roof = get_rgba(rgb[0], rgb[1], rgb[2], 255);
}

