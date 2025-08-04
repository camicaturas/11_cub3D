/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/07/31 15:19:27 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	parse_texture_line_rgb(t_texture_data *texture,
		char *line, t_struct *game_struct)
{
	if (ft_strncmp(line, "F ", 2) == 0 && !(texture->floor))
	{
		texture->floor = parse_texture_path(2, line);
		if (!texture->floor || !is_valid_rgb(texture->floor))
		{
			free(texture->floor);
			texture->floor = NULL;
			error_controller(game_struct, INVALID_RGB);
		}
	}
	else if (ft_strncmp(line, "C ", 2) == 0 && !(texture->roof))
	{
		texture->roof = parse_texture_path(2, line);
		if (!texture->roof || !is_valid_rgb(texture->roof))
		{
			free(texture->roof);
			texture->roof = NULL;
			error_controller(game_struct, INVALID_RGB);
		}
	}
}

void	parse_texture_line(t_texture_data *texture, char *line, t_struct *game_struct)
{
	if (ft_strncmp(line, "NO ", 3) == 0 && !(texture->no))
		texture->no = parse_texture_path(3, line);
	else if (ft_strncmp(line, "WE ", 3) == 0 && !(texture->we))
		texture->we = parse_texture_path(3, line);
	else if (ft_strncmp(line, "EA ", 3) == 0 && !(texture->ea))
		texture->ea = parse_texture_path(3, line);
	else if (ft_strncmp(line, "SO ", 3) == 0 && !(texture->so))
		texture->so = parse_texture_path(3, line);
	else
		parse_texture_line_rgb(texture, line, game_struct);
}

/*
void	parse_texture_line(t_texture_data *texture, char *line, t_struct *game_struct)
{
	if (ft_strncmp(line, "NO ", 3) == 0 && !(texture->no))
		texture->no = parse_texture_path(3, line);
	else if (ft_strncmp(line, "WE ", 3) == 0 && !(texture->we))
		texture->we = parse_texture_path(3, line);
	else if (ft_strncmp(line, "EA ", 3) == 0 && !(texture->ea))
		texture->ea = parse_texture_path(3, line);
	else if (ft_strncmp(line, "SO ", 3) == 0 && !(texture->so))
		texture->so = parse_texture_path(3, line);
	else if (ft_strncmp(line, "F ", 2) == 0 && !(texture->floor))
	{
		texture->floor = parse_texture_path(2, line);
		if (!texture->floor || !is_valid_rgb(texture->floor))
		{
			free(texture->floor);
			texture->floor = NULL;
			error_controller(game_struct, INVALID_RGB);
		}
	}
	else if (ft_strncmp(line, "C ", 2) == 0 && !(texture->roof))
	{
		texture->roof = parse_texture_path(2, line);
		if (!texture->roof || !is_valid_rgb(texture->roof))
		{
			free(texture->roof);
			texture->roof = NULL;
			error_controller(game_struct, INVALID_RGB);
		}
	}
}
*/