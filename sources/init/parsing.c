/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/06/04 11:54:31 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"
/*
int	map_valid(t_struct *game_struct)
{
	int	i;
	int	j;

	j = 0;
	while (game_struct->map[j])
	{
		i = 0;
		while (game_struct->map[j][i] != '\0'
				&& game_struct->map[j][i] != '\n')
		{
			if ((game_struct->map[j][i] != 'C' && game_struct->map[j][i] != 'P'
					&& game_struct->map[j][i] != 'E'
					&& game_struct->map[j][i] != '1'
				&& game_struct->map[j][i] != '0')
					|| i >= game_struct->map_width)
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

void	flood_fill_check(t_struct *game_struct, int y, int x)
{
	if (game_struct->map[y][x] == 'C')
	{
		game_struct->map[y][x] = 'c';
		game_struct->count_collectible++;
	}
	else if (game_struct->map[y][x] == 'P')
	{
		game_struct->map[y][x] = 'p';
		game_struct->count_player++;
	}
	else if (game_struct->map[y][x] == 'E')
	{
		game_struct->map[y][x] = 'e';
		game_struct->count_exit++;
	}
	else if (game_struct->map[y][x] == '0')
	{
		game_struct->map[y][x] = '2';
	}
}

void	flood_fill(int y, int x, t_struct *game_struct)
{
	if (x < 0 || y < 0 || x >= game_struct->map_width
		|| y >= game_struct->map_height)
		return ;
	else if (game_struct->map[y][x] != '0' && game_struct->map[y][x] != 'C'
		&& game_struct->map[y][x] != 'P' && game_struct->map[y][x] != 'E')
		return ;
	flood_fill_check(game_struct, y, x);
	flood_fill(y, x - 1, game_struct);
	flood_fill(y, x + 1, game_struct);
	flood_fill(y - 1, x, game_struct);
	flood_fill(y + 1, x, game_struct);
}
*/



static int	parse_map(t_struct *game_struct, char *line)
{
	char	**tmp;
	int		i;

	if (!line)
		return (0);
	game_struct->minimap.map_height++;
	tmp = malloc(sizeof(char *) * (game_struct->minimap.map_height + 1));
	if (!tmp)
		return (1);
	tmp[game_struct->minimap.map_height] = NULL;
	i = 0;
	while (game_struct->minimap.map_height - 1 > i)
	{
		tmp[i] = game_struct->minimap.map[i];
		i++;
	}
	tmp[i] = line;
	if (game_struct->minimap.map)
		free(game_struct->minimap.map);
	game_struct->minimap.map = tmp;
	return (1);
}

static char	*parse_texture_path(int del, char *line)
{
	char	*path;
	int		len;
	int		i;

	while (line[del] && (line[del] == ' ' || line[del] == '\t'))
		del++;
	len = del;
	while (line[len] && (line[len] != ' ' && line[len] != '\t'))
		len++;
	path = malloc(sizeof(char) * (len - del + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (line[del] && (line[del] != ' '
		&& line[del] != '\t' && line[del] != '\n'))
		path[i++] = line[del++];
	path[i] = '\0';
	while (line[del] && (line[del] == ' ' || line[del] == '\t'))
		del++;
	if (line[del] && line[del] != '\n')
	{
		free(path);
		path = NULL;
	}
	return (path);
}

int	is_valid_rgb(const char *str)
{
	int		count = 0;
	int		value = 0;

	while (*str)
	{
		// Skip leading spaces (if any)
		while (*str == ' ' || *str == '\t')
			str++;

		// Must start with a digit
		if (!ft_isdigit(*str))
			return (0);

		// Parse integer value
		value = 0;
		while (ft_isdigit(*str))
		{
			value = value * 10 + (*str - '0');
			if (value > 255)
				return (0); // RGB component out of range
			str++;
		}
		count++;

		// After value, expect comma or end of string
		if (*str == ',')
			str++;
		else if (*str == '\0')
			break;
		else
			return (0); // Unexpected character
	}

	return (count == 3);
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
	else if (ft_strncmp(line, "F ", 2) == 0 && !(texture->floor))
	{
		texture->floor = parse_texture_path(2, line);
		if (!texture->floor || !is_valid_rgb(texture->floor))
		{
			printf("Error: Invalid floor color format.\n");
			free(texture->floor);
			texture->floor = NULL;
			exit_game(game_struct);
		}
	}
	else if (ft_strncmp(line, "C ", 2) == 0 && !(texture->roof))
	{
		texture->roof = parse_texture_path(2, line);
		if (!texture->roof || !is_valid_rgb(texture->roof))
		{
			printf("Error: Invalid roof color format.\n");
			free(texture->roof);
			texture->roof = NULL;
			exit_game(game_struct);
		}
	}
	
}

void	load_file(t_struct *game_struct, char *file_path)
{
	char	*gnl_readedline;
	int		count_lines;

	count_lines = 1;
	if (!check_extension(file_path))
		exit_more_map_error(game_struct, 11);
	game_struct->fd = open(file_path, O_RDONLY);
	if (game_struct->fd < 0)
		exit_game_error(game_struct, 2);
	while (1)
	{
		//aca tengo que hacer la discriminacion de datos (texturas, color y mapa)
		gnl_readedline = get_next_line(game_struct->fd);	

		if (!gnl_readedline)
			break ;
		// Remove newline if needed
		gnl_readedline = ft_strtrim(gnl_readedline, "\n");

		if (count_lines < 8)
			parse_texture_line(&game_struct->texdata, gnl_readedline, game_struct);
		else if (count_lines > 8 && !parse_map(game_struct, gnl_readedline))	//esto agrega la fila al array en el struct de minimap. 
			break ;
		count_lines++;
	}
	close(game_struct->fd);
	if (game_struct->minimap.map == NULL)
		exit_game_error(game_struct, 5);
	game_struct->minimap.map_width = map_width(game_struct->minimap.map[0]);

if (check_textures(game_struct, &game_struct->texdata) == 1)
		exit_game(game_struct);
}

