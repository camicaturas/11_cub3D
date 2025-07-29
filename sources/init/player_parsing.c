/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/05/26 13:55:13 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	init_player_direction(t_player *player, char nswe)
{
	if (nswe == 'E' || nswe == 'W')
	{
		if (nswe == 'E')
			player->radians = 0;
		else if (nswe == 'W')
			player->radians = PI;
	}
	else if (nswe == 'N' ||nswe == 'S')
	{
		if (nswe == 'N')
			player->radians = 3 * PI05;
		else if (nswe == 'S')
			player->radians = PI05;
	}
}

void	parse_player_spawn_position(t_struct *game_struct, char **map)
{

	int y = 0;
	//Loops through each row of the map.
	while (map[y])
	{
		int x = 0;
		//Loops through each character of the row.
		while (map[y][x])
		{
			//Checks if the current map character is one of the valid player start directions:
			//ft_strchr searches for the first occurrence of a character in a string.
			if (ft_strchr("NSWE", map[y][x]))
			{
				//Sets the player’s position in map space. + 0.5 centers the player in the tile (useful for raycasting).
//				game_struct->player.pos.x = (x + 0.5) * TILE_SIZE; // << no se si deberia ser este el calculo inicial
//				game_struct->player.pos.y = (y + 0.5) * TILE_SIZE; // << no se si deberia ser este el calculo inicial
				game_struct->minimap.player_grid_x = x; // save the current position x
				game_struct->minimap.player_grid_y = y; // save the current position y
				game_struct->minimap.nswe = map[y][x];
				//Sets the direction vector and camera plane based on the NSWE.
				init_player_direction(&game_struct->player, game_struct->minimap.nswe);
				//Replaces the player marker in the map with '0' so it behaves like a walkable floor tile during raycasting and movement.
				map[y][x] = '0'; // replace with walkable space				
				return ;
			}
			x++;
		}
		y++;
	}
}