/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/07/08 13:31:47 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int32_t	main(int ac, char **av)
{
	t_struct	*game_struct;
	t_minimap	minimap_struct;

	(void)ac;
	(void)av;
//////// add later
/*

	parsed = parse_data(av[1], game);
	if (ret)
	{
		free_game(game_struct, parsed);
		exit(EXIT_FAILURE);
	}
*/
/////////

	// esta VALIDACION ES NECESARIA PARA DESPUES, LA DEJO COMENTADA PARA PODER CORRER EL PROGRAMA RAPIDO
	// if (ac != 2)
	//	exit_game_error(&game_struct, 1);

	game_struct = calloc(1, sizeof(t_struct));
	if (!game_struct)
		exit(EXIT_FAILURE);
	init_game(game_struct);
	init_textures(game_struct);
	init_minimap(&minimap_struct);
	init_raycast(game_struct);
	//ESTE ES EL QUE VA
	//load_file(&game_struct, av[1]);
	//load_file(&game_struct, "assets/maps/validmap.cub");
	load_file(game_struct, "assets/maps/invalid/more_numbers_per_color.cub");
	//HAY QUE HACER UN CONTROLLER QUE CHECKEE TODOS los archivos y valide el mapa y las texturas 
	load_textures(game_struct);
	init_player(game_struct);
	new_window(game_struct);
	draw_controller(game_struct);
	hooks(game_struct);
	mlx_loop(game_struct->mlx_ptr);

/*
	check_map(&game_struct);
*/
	return (0);
}
