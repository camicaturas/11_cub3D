/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_controller.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:21:22 by ohosnedl          #+#    #+#             */
/*   Updated: 2025/05/26 13:55:18 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	check_rgb(int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			printf("Invalid RGB value. Provide value between 0 and 255");
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_textures(t_struct *game, t_texture_data *textures)
{

	(void)game;
	(void)textures;

	//HABILITAR LUEGO
/*
	if (!textures->north || !textures->south || !textures->west
		|| !textures->east)
		return (print_error(game->map.path, "Missing textures", FAIL));
	if (!textures->floor || !textures->roof)
		return (print_error(game->map.path, "Missing colors", FAIL));
	if (check_file(textures->north, false) == FAIL
		|| check_file(textures->south, false) == FAIL
		|| check_file(textures->west, false) == FAIL
		|| check_file(textures->east, false) == FAIL
		|| check_rgb(textures->floor) == FAIL
		|| check_rgb(textures->roof) == FAIL)
		return (FAIL);
*/
	textures->hex_floor = rgb_to_hex(textures->floor);
	textures->hex_roof = rgb_to_hex(textures->roof);
	return (0);
}

//safely free memory allocated by ft_split, which returns a dynamically allocated array of strings 
void	free_split(char **split)
{
	int	i;

	if (!split)
		return;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	parse_rgb(char *str, int *rgb)
{
	char	**split;
	int		i;

	split = ft_split(str, ',');
	if (!split)
	{
		ft_putstr_fd("RGB parsing failed\n", 2);
		exit(1);
	}
	i = 0;
	while (i < 3)
	{
		rgb[i] = ft_atoi(split[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			ft_putstr_fd("RGB value out of range\n", 2);
			exit(1);
		}
		i++;
	}
	free_split(split);
}

void	load_textures(t_struct *game_struct)
{
	int	rgb[3];
	game_struct->texture.north = mlx_load_png(game_struct->texdata.no);
	game_struct->texture.south = mlx_load_png(game_struct->texdata.so);
	game_struct->texture.east = mlx_load_png(game_struct->texdata.ea);
	game_struct->texture.west = mlx_load_png(game_struct->texdata.we);
	parse_rgb(game_struct->texdata.floor, rgb);
	game_struct->texture.color_floor = get_rgba(rgb[0], rgb[1], rgb[2], 255);
	parse_rgb(game_struct->texdata.roof, rgb);
	game_struct->texture.color_roof = get_rgba(rgb[0], rgb[1], rgb[2], 255);
	//game_struct->item.texture_item = mlx_load_png("./assets/textures/item.png");
	// if (!game_struct->item.texture)
		//exit_game_error(g, 4);

}


/*
static void	init_texture(t_struct *game_struct)
{
	game_struct->player = mlx_load_png("./assets/textures/player.png");
	game_struct->player_img = mlx_texture_to_image(game_struct->mlx_ptr,game_struct->player);
	game_struct->wall = mlx_load_png("./assets/textures/wall.png");
	game_struct->wall_img = mlx_texture_to_image(game_struct->mlx_ptr, game_struct->wall);
	game_struct->collectible = mlx_load_png("./assets/textures/collectible.png");
	game_struct->collectible_img = mlx_texture_to_image(game_struct->mlx_ptr, game_struct->collectible);
	game_struct->floor = mlx_load_png("./assets/textures/floor.png");
	game_struct->floor_img = mlx_texture_to_image(game_struct->mlx_ptr, game_struct->floor);
	game_struct->exit = mlx_load_png("./assets/textures/exit.png");
	game_struct->exit_img = mlx_texture_to_image(game_struct->mlx_ptr, game_struct->exit);
	if (!game_struct->player || !game_struct->wall || !game_struct->collectible	|| !game_struct->floor || !game_struct->exit)
		exit_game_error(game_struct, 4);
}
*/



/*
static void	render_texture(t_struct *game_struct, int y, int x)
{
	if (game_struct->map[y][x] == '1')
		if (mlx_image_to_window(game_struct->mlx_ptr, game_struct->wall_img,
				x * game_struct->map_tile_width, y
				* game_struct->map_tile_height) < 0)
			exit_game_error(game_struct, 4);
	if (game_struct->map[y][x] == '2' || game_struct->map[y][x] == 'c'
			|| game_struct->map[y][x] == 'p'
			|| game_struct->map[y][x] == 'e')
		if (mlx_image_to_window(game_struct->mlx_ptr, game_struct->floor_img,
				x * game_struct->map_tile_width, y
				* game_struct->map_tile_height) < 0)
			exit_game_error(game_struct, 4);
	if (game_struct->map[y][x] == 'c')
		if (mlx_image_to_window(game_struct->mlx_ptr,
				game_struct->collectible_img,
				x * game_struct->map_tile_width, y
				* game_struct->map_tile_height) < 0)
			exit_game_error(game_struct, 4);
	if (game_struct->map[y][x] == 'e')
		if (mlx_image_to_window(game_struct->mlx_ptr, game_struct->exit_img,
				x * game_struct->map_tile_width, y
				* game_struct->map_tile_height) < 0)
			exit_game_error(game_struct, 4);
}
*/

/*
void	load_textures(t_struct *game_struct)
{
	int	y;
	int	x;

	y = 0;
	init_texture(game_struct);
	while (game_struct->map[y])
	{
		x = 0;
		while (game_struct->map[y][x])
		{
			render_texture(game_struct, y, x);
			x++;
		}
		y++;
	}
	game_struct->player_img = mlx_texture_to_image(game_struct->mlx_ptr,
			game_struct->player);
	if (mlx_image_to_window(game_struct->mlx_ptr, game_struct->player_img,
			game_struct->player_x * game_struct->map_tile_width,
			game_struct->player_y * game_struct->map_tile_height) < 0)
		exit_game_error(game_struct, 4);
	if (!game_struct->player_img || !game_struct->wall_img
		|| !game_struct->collectible_img
		|| !game_struct->floor_img || !game_struct->exit_img)
		exit_game_error(game_struct, 4);
}
*/
