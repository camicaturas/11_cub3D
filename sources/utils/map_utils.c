/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/07/31 17:23:34 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	restore_map(t_struct *game_struct)
{
	int	y;
	int	x;

	y = 0;
	while (y < game_struct->minimap.map_height)
	{
		x = 0;
		while (x < game_struct->minimap.map_width)
		{
		if (game_struct->minimap.map[y][x] == '2')
				game_struct->minimap.map[y][x] = '0';
		x++;
		}
	y++;
	}
}

void	clear_textures(t_texture *texture)
{
	if (texture->north)
		mlx_delete_texture(texture->north);
	if (texture->south)
		mlx_delete_texture(texture->south);
	if (texture->west)
		mlx_delete_texture(texture->west);
	if (texture->east)
		mlx_delete_texture(texture->east);
	texture->north = NULL;
	texture->south = NULL;
	texture->east = NULL;
	texture->west = NULL;
}

int	map_width(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	return (i);
}

void	map_free(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	flood_fill(int y, int x, t_struct *game_struct)
{
	char current;

	if (y < 0 || y >= game_struct->minimap.map_height)
		error_controller(game_struct, MAP_NOT_CLOSED);
	if (x < 0 || x >= (int)ft_strlen(game_struct->minimap.map[y]))
		error_controller(game_struct, MAP_NOT_CLOSED);
	current = game_struct->minimap.map[y][x];
	if (current == '1' || current == '2')
		return ;
	if (current == '0' || current == ' ' || current == 'N'
		|| current == 'S' || current == 'E' || current == 'W')
		game_struct->minimap.map[y][x] = '2';
	else
		error_controller(game_struct, MAP_NOT_CLOSED);
	flood_fill(y, x - 1, game_struct);
	flood_fill(y, x + 1, game_struct);
	flood_fill(y - 1, x, game_struct);
	flood_fill(y + 1, x, game_struct);
}
