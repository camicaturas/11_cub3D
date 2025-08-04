/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_controller.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/07/31 15:19:56 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

const	char *error_messages_list[ERRMAX] = 
{
	"No Errors",
	"Error #1: Not enough arguments. Use: ./cub3d <assets/maps/mapname.cub>\n",
	"Error #2: Invalid file descriptor\n",
	"Error #3: Map borders not closed\n",
	"Error #4: Loading textures failed\n",
	"Error #5: Empty file\n",
	"Error #6: There's no Player spawn in the Map\n",
	"Error #7: Map parsing error — line memory (double free or leak)\n",
	"Error #8: Invalid RGB (0-255) color format.\n",
	"Error #9: Tiles too big! Doesn't fit in the screen\n",
	"Error #10: Malloc Failed\n",
	"Error #11: Invalid map extension, has to be .cub\n",
	"Error #12: Missing texture!\n",
	"Error #13: Missing Map colors!\n",
	"Error #14: Is not a PNG file\n",
	"Error #15: No such file or directory\n",
	"Error #16: Is a directory\n",
	"Error #17: Floor color is not set or is Wrong\n",
	"Error #18: Ceiling color is not set or is Wrong\n",
	"Error #19: Map has invalid characters. Use 0 1 N S E W and spaces.\n",
	"Error #20: Invalid map height. Has to have 3 rows minimum.\n",
	"Error #21: Two or more players spaws (N S W E) found\n",
	"Exit game\n",
};

void	free_graphics(t_struct *game_struct)
{
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
	if (game_struct->mlx_ptr)
	{
		mlx_terminate(game_struct->mlx_ptr);
		game_struct->mlx_ptr = NULL;
	}
}

void	free_game_data(t_struct *game_struct)
{
	clear_textures(&game_struct->texture);
	free(game_struct->texdata.no);
	free(game_struct->texdata.so);
	free(game_struct->texdata.ea);
	free(game_struct->texdata.we);
	free(game_struct->texdata.floor);
	free(game_struct->texdata.roof);
	game_struct->texdata.no = NULL;
	game_struct->texdata.so = NULL;
	game_struct->texdata.ea = NULL;
	game_struct->texdata.we = NULL;
	game_struct->texdata.floor = NULL;
	game_struct->texdata.roof = NULL;
	if (game_struct->ray)
	{
		free(game_struct->ray);
		game_struct->ray = NULL;
	}
	if (game_struct->minimap.map)
	{
		map_free(game_struct->minimap.map);
		game_struct->minimap.map = NULL;
	}
}

void	exit_game(t_struct *game_struct)
{
	if (!game_struct)
	{
		fprintf(stderr, "exit_game() called with NULL!\n");
		exit(EXIT_FAILURE);
	}
	free_graphics(game_struct);
	free_game_data(game_struct);
	ft_printf("\n\033[1;32mGame exited successfully!");
	ft_printf(" Thanks for playing Cub3D!! :)\033[0m\n\n");
	free(game_struct);
	exit(EXIT_SUCCESS);
}

void	error_controller(t_struct *game_struct, int error_id)
{
	if (error_id == EXIT_GAME)
		exit_game(game_struct);
	else if (error_id >= 0 && error_id < ERRMAX)
		fprintf(stderr, "\033[1;31m%s\033[0m", error_messages_list[error_id]);
	else
		fprintf(stderr, "\033[1;31mUnknown error occurred.\033[0m\n");
	exit_game(game_struct);
}

