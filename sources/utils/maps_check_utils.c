/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_check_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/07/31 15:18:59 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

bool	is_dir(char *arg)
{
	struct stat path_stat;

	if (stat(arg, &path_stat) != 0)
		return (false);
	return S_ISDIR(path_stat.st_mode);
}

bool	check_extension(char *map_path, char *extension)
{
	int	map_len;
	int	ext_len;
	int	i;

	map_len = ft_strlen(map_path);
	ext_len = ft_strlen(extension);
	if (map_len < ext_len)
		return (0);
	i = 0;
	while (i < ext_len)
	{
		if (map_path[map_len - ext_len + i] != extension[i])
			return (0);
		i++;
	}
	return (1);
}

int	verify_file_integrity(t_struct *game_struct,
		char *file_path, char *filetype)
{
	int	fd;

	if (is_dir(file_path))
		error_controller(game_struct, IS_DIRECTORY);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		error_controller(game_struct, FILE_NOT_FOUND);
	close(fd);
	if (strcmp(filetype, "map") == 0 && !check_extension(file_path, "cub"))
		error_controller(game_struct, INVALID_EXTENSION);
	if (strcmp(filetype, "texture") == 0 && !check_extension(file_path, "png"))
		error_controller(game_struct, NOT_PNG);
	return (1);
}
