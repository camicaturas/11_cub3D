/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/07/31 15:28:37 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	init_game(t_struct *game_struct)
{
	game_struct->fd = 0;
	game_struct->player_x = 0;
	game_struct->player_y = 0;
	game_struct->screen_width = 1920;
	game_struct->screen_height = 1080;
	game_struct->minimap.map = NULL;
	game_struct->mlx_ptr = NULL;
}

void	init_textures(t_struct *game_struct)
{
	game_struct->texture.north = NULL;
	game_struct->texture.south = NULL;
	game_struct->texture.east = NULL;
	game_struct->texture.west = NULL;
	game_struct->texture.color_floor = 0;
	game_struct->texture.color_roof = 0;
	game_struct->texdata.no = NULL;
	game_struct->texdata.so = NULL;
	game_struct->texdata.ea = NULL;
	game_struct->texdata.we = NULL;
	game_struct->texdata.floor = NULL;
	game_struct->texdata.roof = NULL;
	game_struct->texdata.hex_floor = 0;
	game_struct->texdata.hex_roof = 0;
}

void	init_minimap(t_minimap *t_minimap)
{
	t_minimap->map_width = 0;
	t_minimap->map_height = 0;
	t_minimap->player_grid_x = 0;
	t_minimap->player_grid_y = 0;
	t_minimap->nswe ='\0';
	t_minimap->map = ft_calloc(1, sizeof(char *));
	if (!t_minimap->map)
	{
		ft_printf("Error: Failed to allocate memory for minimap.\n");
		exit(EXIT_FAILURE);
	}
}

void	init_player(t_struct *game_struct)
{
	game_struct->player.dir.x = 0;
	game_struct->player.dir.y = 0;
	game_struct->player.plane.x = 0;
	game_struct->player.plane.y = 0;
	game_struct->player.move.x = 0;
	game_struct->player.move.y = 0;
	game_struct->player.next_pos.x = 0;
	game_struct->player.next_pos.y = 0;
	game_struct->player.radians = 0;
	game_struct->player.fov_in_radians = FOV * (PI / 180);
	game_struct->player.rot_speed = ROTATION_SPEED;
	parse_player_spawn_position(game_struct, game_struct->minimap.map);
	game_struct->player.pos.x = floor(game_struct->minimap.player_grid_x
		* TILE_SIZE + TILE_SIZE / 2);
	game_struct->player.pos.y = floor(game_struct->minimap.player_grid_y
		* TILE_SIZE + TILE_SIZE / 2);
}

void	init_raycast(t_struct *game_struct)
{
	game_struct->ray = ft_calloc(1, sizeof(t_ray));
	if (!game_struct->ray)
	{
		ft_printf("Error: Failed to allocate memory for raycast.\n");
		exit(EXIT_FAILURE);
	}
	game_struct->ray->distance = 0;
	game_struct->ray->hit_x = 0;
	game_struct->ray->hit_y = 0;
	game_struct->ray->hit_vertical = 0;
	game_struct->ray->map_x = 0;
	game_struct->ray->map_y = 0;
	game_struct->ray->ray_angle = 0;
}
