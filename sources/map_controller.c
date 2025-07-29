/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/05/27 11:29:02 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	check_tilesize(t_struct *game_struct)
{
	if (game_struct->map_width * game_struct->map_tile_width
		> game_struct->screen_width
		|| game_struct->map_height * game_struct->map_tile_height
		> game_struct->screen_height)
		return (0);
	return (1);
}

int	check_map_shape(t_struct *game_struct)
{
	if (game_struct->map_width == game_struct->map_height)
		return (0);
	return (1);
}

void	check_map(t_struct *game_struct)
{
	if (!check_borders(game_struct))
		exit_more_map_error(game_struct, 3);
	if (!map_valid(game_struct))
		exit_more_map_error(game_struct, 3);
	if (!check_map_shape(game_struct))
		exit_map_error(game_struct, 10);
	player_spawn_position(game_struct);
	flood_fill(game_struct->player_y, game_struct->player_x, game_struct);
	if (!check_player_spawn(game_struct))
		exit_map_error(game_struct, 6);
	if (!check_exit(game_struct))
		exit_map_error(game_struct, 7);
	if (!check_count_collectibles(game_struct))
		exit_map_error(game_struct, 8);
	if (!check_tilesize(game_struct))
		exit_more_map_error(game_struct, 9);
}
