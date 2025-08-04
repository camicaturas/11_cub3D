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

int	check_if_all_textures_loaded(t_texture_data *texdata)
{
	return (
		texdata->no && texdata->so &&
		texdata->ea && texdata->we &&
		texdata->floor && texdata->roof
	);
}

int	parse_map(t_struct *game_struct, char *line)
{
	char	**tmp;
	int		i;

	if (!line)
		return (0);
	if(map_width(line) > game_struct->minimap.map_width)
		game_struct->minimap.map_width = map_width(line);
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

char	*parse_texture_path(int del, char *line)
{
	char	*path;
	int		i;
	int		j;

	i = del;
	j = 0;
	path = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!path)
		return (NULL);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != '\t')
			path[j++] = line[i];
		i++;
	}
	path[j] = '\0';
	return (path);
}

static int	parse_rgb_component(const char **str)
{
	int value;

	value = 0;
	while (ft_isdigit(**str))
	{
		value = value * 10 + (**str - '0');
		if (value > 255)
			return (0);
		(*str)++;
	}
	return (1);
}

int	is_valid_rgb(const char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str == ' ' || *str == '\t')
			str++;
		if (!ft_isdigit(*str))
			return (0);
		if (!parse_rgb_component(&str))
			return (0);
		count++;
		if (*str == ',')
			str++;
		else if (*str == '\0')
			break ;
		else
			return (0);
	}
	return (count == 3);
}

/*
int	is_valid_rgb(const char *str)
{
	int	count;
	int	value;
	
	count = 0;
	value = 0;
	while (*str)
	{
		while (*str == ' ' || *str == '\t')
			str++;
		if (!ft_isdigit(*str))
			return (0);
		value = 0;
		while (ft_isdigit(*str))
		{
			value = value * 10 + (*str - '0');
			if (value > 255)
				return (0);
			str++;
		}
		count++;
		if (*str == ',')
			str++;
		else if (*str == '\0')
			break ;
		else
			return (0);
	}
	return (count == 3);
}
*/