/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/05/27 15:20:21 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

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
}

//calculates the width of a map line by counting how many characters are in a string before a newline ('\n') or the end of the string ('\0').
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

void	exit_game(t_struct *game_struct)
{
	if (game_struct->minimap.map)
		map_free(game_struct->minimap.map);
	clear_textures(&game_struct->texture);
	free(game_struct->ray);
	if (game_struct->mlx_ptr)
		mlx_terminate(game_struct->mlx_ptr);

	printf("TODO ROTO LOCO!.\n");

	exit(EXIT_FAILURE);
}


/*
HACER UNA VALIDACION PARA ESTO LUEGO
borra los pointers a la imagenes y al ptrx
	if (game_struct->minimap_img)
		mlx_delete_image(game_struct->mlx_ptr, game_struct->minimap_img);
	if (game_struct->main_img)
		mlx_delete_image(game_struct->mlx_ptr, game_struct->main_img);
	if (game_struct->mlx_ptr)
		mlx_close_window(game_struct->mlx_ptr);
*/