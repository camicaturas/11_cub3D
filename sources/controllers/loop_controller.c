/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_controller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/07/31 15:19:54 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	on_window_close(void *param)
{
	t_struct *game_struct = (t_struct *)param;
	error_controller(game_struct, EXIT_GAME);
}

/*
 * controls the hook iteration
 * called in hooks_controller
 * 1) if you press ESC the game ends (exit game deletes everything)
 * 2) if some key is press (ft_keyboard) it calls to the draw controller
 * to draw what is need it in the screen
 */
void	loop_controller(void *param)
{
	t_struct *game_struct = (t_struct *)param;

	ft_keyboard(game_struct); // This should update player position if keys are pressed
	// Always draw each frame
	draw_controller(game_struct);
	//items_controller(game_struct); // ITEMS if doesnt work DELETE IT
	if (mlx_is_key_down(game_struct->mlx_ptr, MLX_KEY_ESCAPE))
	{
		error_controller(game_struct, EXIT_GAME);
		mlx_close_window(game_struct->mlx_ptr);
	}
}

void	hooks(t_struct *game_struct)
{
	mlx_loop_hook(game_struct->mlx_ptr, loop_controller, game_struct);
	mlx_close_hook(game_struct->mlx_ptr, &on_window_close, game_struct);
}

