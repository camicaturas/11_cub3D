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

int	is_line_blank(const char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n' && *line != '\r')
			return (0);
		line++;
	}
	return (1);
}

static int	process_texture_or_map_line(
	t_struct *game_struct, char *line, int *all_textures_loaded)
{
	if (is_line_blank(line))
	{
		free(line);
		return (1);
	}
	if (!(*all_textures_loaded))
	{
		parse_texture_line(&game_struct->texdata, line, game_struct);
		*all_textures_loaded =
			check_if_all_textures_loaded(&game_struct->texdata);
	}
	else
	{
		if (!parse_map(game_struct, line))
		{
			free(line);
			return (0);
		}
		line = NULL;
	}
	if (line)
		free(line);
	return (1);
}

void	process_map_file_lines(t_struct *game_struct)
{
	char	*line;
	int		all_textures_loaded;

	all_textures_loaded = 0;
	while ((line = get_next_line(game_struct->fd)))
	{
		if (!process_texture_or_map_line(game_struct, line, &all_textures_loaded))
			break;
	}
}

/*
void	process_map_file_lines(t_struct *game_struct)
{
	char	*line;
	int		all_textures_loaded;

	all_textures_loaded = 0;
	while ((line = get_next_line(game_struct->fd)))
	{
		if (is_line_blank(line))
		{
			free(line);
			continue;
		}
		if (!all_textures_loaded)
		{
			parse_texture_line(&game_struct->texdata, line, game_struct);
			all_textures_loaded = 
				check_if_all_textures_loaded(&game_struct->texdata);
		}
		else
		{
			if (!parse_map(game_struct, line))
			{
				free(line);
				break;
			}
			line = NULL;
		}
		if (line)
			free(line);
	}
}
*/

static void	validate_map_height(t_struct *game_struct)
{
	if (game_struct->minimap.map_height < 3)
		error_controller(game_struct, INVALID_MAP_HEIGTH);
}

void	load_file(t_struct *game_struct, char *file_path)
{
	if(!file_path)
		error_controller(game_struct, ARGC_TOO_FEW);
	if (!check_extension(file_path, "cub"))
		error_controller(game_struct, INVALID_EXTENSION);
	game_struct->fd = open(file_path, O_RDONLY);
	if (game_struct->fd < 0)
		error_controller(game_struct, INVALID_FILE_DESCRIPTOR);
	process_map_file_lines(game_struct);
	close(game_struct->fd);
	if (game_struct->minimap.map == NULL)
		error_controller(game_struct, FILE_EMPTY);
	validate_map_chars(game_struct);
	validate_map_height(game_struct);

	if (validate_textures(&game_struct->texdata, game_struct) == 1)
		error_controller(game_struct, TEXTURE_MISSING);
}
