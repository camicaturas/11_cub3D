/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/07/31 16:07:19 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int32_t	main(int ac, char **av)
{
	t_struct	*game_struct;
	t_minimap	minimap_struct;

	(void)ac;
	(void)av;

	// esta VALIDACION ES NECESARIA PARA DESPUES, LA DEJO COMENTADA PARA PODER CORRER EL PROGRAMA RAPIDO
	// if (ac != 2)
	//	exit_game_error(&game_struct, 1);

	game_struct = ft_calloc(1, sizeof(t_struct));
	if (!game_struct)
		exit(EXIT_FAILURE);
	init_game(game_struct);
	init_textures(game_struct);
	init_minimap(&minimap_struct);
	init_raycast(game_struct);

	//ESTE ES EL QUE VA
	//load_file(game_struct, av[1]);
	//load_file(game_struct, "assets/maps/map0.cub");
	//load_file(game_struct, "assets/maps/validmap.cub");
	//load_file(game_struct, "assets/maps/invalid/more_numbers_per_color.cub");
	//load_file(game_struct, "assets/maps/validmap7.cub");
	//load_file(game_struct, "assets/maps/map1.cub");
	//load_file(game_struct, "assets/maps/map8.cub");
	load_file(game_struct, "assets/maps/square.cub");
	load_textures(game_struct);
	init_player(game_struct);
	map_controller(game_struct);
	new_window(game_struct);
	draw_controller(game_struct);
	hooks(game_struct);
	mlx_loop(game_struct->mlx_ptr);
	return (0);
}



//things that are missing so far:
/*

✅flood fill gives me segmentation fault when the map founds an empty space
✅ the parsing is no freeing the memory correctly
✅ checking the walls if the map is correct (validated), check with the subject
✅ check all the errors, one by one if they apply to every situation
✅  handle the errors and the data correctly, right now the program is just printing an error and that's it (point 4). Do a function that check the error, free the memory with exit_game() and prints the error. check the exit_game_error function to re do it and check exit_map_error_message also.
✅ check the function map_controller if its working correctly for checking the map
✅ when you close with the cross you have to manage the memory leak, now is not working.
✅ if there is no intial starting point the player spaws in some random place
✅ map_controller tiene que chequear y salir del programa si algo sale mal (con flood fill )
✅ when your parsing or testing the flood fill, the empty spaces ' ' make the program crash, handle the ' '
✅ There may be gaps in the file to be parsed and lines between texture data, no that is not handled.
✅ when an unespected error happens return an error and free all the memory. an error like a textures was not loaded or the map was not parsed


MINOR ADJUSTMENTs:
12) for some reason, doesnt allow to keep the corner of the top right empty, even if its surrounded by walls.
13) do a check that cannot 2 spawns positions (cannot be more than 1 NSEW)
14) do a check that the map has to be bigger that 2 rows and 2 colums,
15) add this errors: TILE_TOO_BIG, ARGC_TOO_FEW
17) when the map is changed from the top the minimap is working but when you do the bottom bigger than the top doesnt work

TESTs TO DO IN THE SCHOOL BEFORE PUSH
1) normiette
✅ valgrind when yoou check for leaks when yoou close the window with ESC and the cross of the window
✅ valgrind when something crashes because didnt loaded properly (textures, map, etc)
4) make the program is run when you use the  ARGUMENTS (now is the loading is hardcoded)
5) check for memory leaks

FOR MAC:
leaks --atExit -- ./cube3d
*/
