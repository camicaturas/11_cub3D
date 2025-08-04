/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/07/31 15:19:01 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	handle_strafing(t_struct *game)
{
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_A))
	{
		game->player.move.x += sin(game->player.radians) * PLAYER_SPEED;
		game->player.move.y -= cos(game->player.radians) * PLAYER_SPEED;
	}
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_D))
	{
		game->player.move.x -= sin(game->player.radians) * PLAYER_SPEED;
		game->player.move.y += cos(game->player.radians) * PLAYER_SPEED;
	}
}

static void	handle_forward_backward(t_struct *game)
{
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_W) ||
		mlx_is_key_down(game->mlx_ptr, MLX_KEY_UP))
	{
		game->player.move.x += cos(game->player.radians) * PLAYER_SPEED;
		game->player.move.y += sin(game->player.radians) * PLAYER_SPEED;
	}
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_S) ||
		mlx_is_key_down(game->mlx_ptr, MLX_KEY_DOWN))
	{
		game->player.move.x -= cos(game->player.radians) * PLAYER_SPEED;
		game->player.move.y -= sin(game->player.radians) * PLAYER_SPEED;
	}
}

void	handle_movement_keys(t_struct *game)
{
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_LEFT))
		rotate_player(game, MLX_KEY_LEFT);
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_RIGHT))
		rotate_player(game, MLX_KEY_RIGHT);
	handle_forward_backward(game);
	handle_strafing(game);
}

/*
void	handle_movement_keys(t_struct *game)
{
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_LEFT))
		rotate_player(game, MLX_KEY_LEFT);
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_RIGHT))
		rotate_player(game, MLX_KEY_RIGHT);
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_W) || 
		mlx_is_key_down(game->mlx_ptr, MLX_KEY_UP))
	{
		game->player.move.x += cos(game->player.radians) * PLAYER_SPEED;
		game->player.move.y += sin(game->player.radians) * PLAYER_SPEED;
	}
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_S) || 
		mlx_is_key_down(game->mlx_ptr, MLX_KEY_DOWN))
	{
		game->player.move.x -= cos(game->player.radians) * PLAYER_SPEED;
		game->player.move.y -= sin(game->player.radians) * PLAYER_SPEED;
	}
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_A))
	{
		game->player.move.x += sin(game->player.radians) * PLAYER_SPEED;
		game->player.move.y -= cos(game->player.radians) * PLAYER_SPEED;
	}
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_D))
	{
		game->player.move.x -= sin(game->player.radians) * PLAYER_SPEED;
		game->player.move.y += cos(game->player.radians) * PLAYER_SPEED;
	}
}
*/
void	ft_keyboard(void *param)
{
	t_struct *game_struct = (t_struct *)param;
 	double temp_radians;

	game_struct->player.move.x = 0;
	game_struct->player.move.y = 0;
	temp_radians = game_struct->player.radians;
	handle_movement_keys(game_struct);
	if (game_struct->player.move.x != 0 || game_struct->player.move.y != 0
			|| game_struct->player.radians != temp_radians)
	{
		normalize_movement(game_struct);
		ft_player_movement(game_struct);
	}
}
