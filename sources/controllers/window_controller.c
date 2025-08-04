/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/07/31 15:19:48 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	get_rgba(int r, int g, int b, int a)
{
	return ((a & 0xFF) << 24) | ((r & 0xFF) << 16) |
	((g & 0xFF) << 8) | (b & 0xFF);
}

int	finalize_image_creation(t_struct *game_struct)
{
	if (!game_struct->main_img || !game_struct->minimap_img)
	{
		printf("Image creation failed: %s\n", mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	mlx_image_to_window(game_struct->mlx_ptr, game_struct->main_img, 0, 0);
	mlx_set_instance_depth(&game_struct->main_img->instances[0], 0);
	mlx_image_to_window(game_struct->mlx_ptr,
		game_struct->minimap_img, 10, 10);
	mlx_set_instance_depth(&game_struct->minimap_img->instances[0], 1);
	return (1);
}

int	draw_new_image(t_struct *game_struct)
{
	int	mm_screen_width;
	int	mm_screen_height;

	mm_screen_width = MINIMAP_TILE_SIZE * game_struct->minimap.map_width;
	mm_screen_height = MINIMAP_TILE_SIZE * game_struct->minimap.map_height;
	if (game_struct->main_img)
	{
		mlx_delete_image(game_struct->mlx_ptr, game_struct->main_img);
		game_struct->main_img = NULL;
	}
	if (game_struct->minimap_img)
	{
		mlx_delete_image(game_struct->mlx_ptr, game_struct->minimap_img);
		game_struct->minimap_img = NULL;
	}
	game_struct->main_img = mlx_new_image(game_struct->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	game_struct->minimap_img = mlx_new_image(game_struct->mlx_ptr,
			mm_screen_width, mm_screen_height);
	return (finalize_image_creation(game_struct));
}

int	new_window(t_struct *game_struct)
{
	game_struct->mlx_ptr = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d 2D map", false);
	if (!game_struct->mlx_ptr)
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	return (1);
}
