/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/05/26 13:54:53 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

bool	is_walkable(t_struct *game_struct, int y, int x)
{
	// Map Bounds check (el mapa de testeo mide x=18 y=10)
	if (y < 0 || y > game_struct->minimap.map_height || x < 0 || x > game_struct->minimap.map_width)
		return false;

	if (game_struct->minimap.map[y][x] == '1')
		return (false);
	return (true);
}

//Normalizes the player's movement vector and then scales it to a constant speed (PLAYER_SPEED)
//Without normalization, the player would move faster diagonally 
void	normalize_movement(t_struct *game_struct)
{
	double	len;

	len = sqrt(game_struct->player.move.x * game_struct->player.move.x + game_struct->player.move.y * game_struct->player.move.y);
	if (len > 0)
	{
		game_struct->player.move.x = (game_struct->player.move.x / len) * PLAYER_SPEED;
		game_struct->player.move.y = (game_struct->player.move.y / len) * PLAYER_SPEED;
	}
}

void	ft_player_movement(t_struct *game_struct)
{
	double	next_pos_x = game_struct->player.pos.x + game_struct->player.move.x;
	double	next_pos_y = game_struct->player.pos.y + game_struct->player.move.y;

	int grid_x = (int)(next_pos_x / TILE_SIZE);
	int grid_y = (int)(game_struct->player.pos.y / TILE_SIZE);
	if (is_walkable(game_struct, grid_y, grid_x))
		game_struct->player.pos.x = next_pos_x;
	grid_y = (int)(next_pos_y / TILE_SIZE);
	grid_x = (int)(game_struct->player.pos.x / TILE_SIZE);
	if (is_walkable(game_struct, grid_y, grid_x))
		game_struct->player.pos.y = next_pos_y;
}


void	handle_movement_keys(t_struct *game_struct)
{
	if (mlx_is_key_down(game_struct->mlx_ptr, MLX_KEY_LEFT))
		rotate_player(game_struct, MLX_KEY_LEFT);
	if (mlx_is_key_down(game_struct->mlx_ptr, MLX_KEY_RIGHT))
		rotate_player(game_struct, MLX_KEY_RIGHT);
	if (mlx_is_key_down(game_struct->mlx_ptr, MLX_KEY_W) || 
		mlx_is_key_down(game_struct->mlx_ptr, MLX_KEY_UP))
	{
		game_struct->player.move.x += cos(game_struct->player.radians) * PLAYER_SPEED;
		game_struct->player.move.y += sin(game_struct->player.radians) * PLAYER_SPEED;
	}
	if (mlx_is_key_down(game_struct->mlx_ptr, MLX_KEY_S) || 
		mlx_is_key_down(game_struct->mlx_ptr, MLX_KEY_DOWN))
	{
		game_struct->player.move.x -= cos(game_struct->player.radians) * PLAYER_SPEED;
		game_struct->player.move.y -= sin(game_struct->player.radians) * PLAYER_SPEED;
	}
	if (mlx_is_key_down(game_struct->mlx_ptr, MLX_KEY_A))
	{
		game_struct->player.move.x += sin(game_struct->player.radians) * PLAYER_SPEED;
		game_struct->player.move.y -= cos(game_struct->player.radians) * PLAYER_SPEED;
	}
	if (mlx_is_key_down(game_struct->mlx_ptr, MLX_KEY_D))
	{
		game_struct->player.move.x -= sin(game_struct->player.radians) * PLAYER_SPEED;
		game_struct->player.move.y += cos(game_struct->player.radians) * PLAYER_SPEED;
	}
}

void	ft_keyboard(void *param)
{
	t_struct *game_struct = (t_struct *)param;
 	double temp_radians;

	// Reset movement
	game_struct->player.move.x = 0;
	game_struct->player.move.y = 0;
	temp_radians = game_struct->player.radians;

	// Apply directional input and rotate calculation
	handle_movement_keys(game_struct);

	// If any movement occurred, normalize and move
	if (game_struct->player.move.x != 0 || game_struct->player.move.y != 0 || game_struct->player.radians != temp_radians)
	{
		normalize_movement(game_struct);
		ft_player_movement(game_struct);
	}
}
