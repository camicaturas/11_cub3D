/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:12:05 by ohosnedl          #+#    #+#             */
/*   Updated: 2025/07/31 15:46:57 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../lib/libft_exp/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>

# define WINDOW_WIDTH			1024
# define WINDOW_HEIGHT			512
# define PI						3.141592653589793238462643383279502884197169
# define PI05					1.570796326794896619231321691639751442098584
# define MINIMAP_TILE_SIZE 		10
# define MINIMAP_PLAYER_SIZE 	5
# define TILE_SIZE				10
# define FOV					60
# define PLAYER_SPEED			0.7
# define ROTATION_SPEED			0.06

# define RED					0xFF0000FF
# define GREEN					0x00FF00FF
# define BLUE					0x0000FFFF
# define YELLOW					0xFFFF00FF
# define CYAN					0xFF00FFFF
# define MAGENTA				0xFFFF00FF
# define WHITE					0xFFFFFFFF
# define BLACK					0x000000FF
# define GRAY					0xAAAAAAFF
# define LIGHT_GRAY				0xCCCCCCFF
# define DARK_GRAY				0x444444FF
# define DARK_GRAY_TRANSPARENT	0x44444470

# define COLOR_WALL				RED
# define COLOR_FLOOR			YELLOW
# define COLOR_PLAYER			BLUE
# define COLOR_ITEM				GREEN

// config
# define TEXTURED_WALLS			1
# define SHOW_FOV				1
# define SHOW_MAP				1
# define SHOW_MAP_GRID			0
# define SHOW_CHARACTER			1
# define SHOW_DIRECTION_LINE	1

typedef enum e_error_list
{
	NO_ERROR = 0,
	ARGC_TOO_FEW,
	INVALID_FILE_DESCRIPTOR,
	MAP_NOT_CLOSED,
	TEXTURE_LOAD_FAIL,
	FILE_EMPTY,
	NO_PLAYER_SPAWN,
	ERR_INVALID_MAP,
	INVALID_RGB,
	TILE_TOO_BIG,
	ERR_MALLOC_FAILED,
	INVALID_EXTENSION,
	TEXTURE_MISSING,
	COLOR_MISSING,
	NOT_PNG,
	FILE_NOT_FOUND,
	IS_DIRECTORY,
	FLOOR_COLOR_INVALID,
	CEILING_COLOR_INVALID,
	INVALID_MAP_CHAR,
	INVALID_MAP_HEIGTH,
	MULTI_SPAWNS,
	EXIT_GAME,
	ERRMAX
} t_error_list;

typedef struct s_texture
{
	int				color_roof;
	int				color_floor;
	mlx_texture_t	*east;
	mlx_texture_t	*north;
	mlx_texture_t	*west;
	mlx_texture_t	*south;
}	t_texture;

typedef struct s_texdata
{
	char			*ea;
	char			*no;
	char			*we;
	char			*so;
	char			*roof;
	char			*floor;
	unsigned long	hex_roof;
	unsigned long	hex_floor;
}	t_texture_data;

typedef struct s_ray
{
	int		ray_index;
	double	intersect_horz_x;
	double	intersect_horz_y;
	double	intersect_vert_x;
	double	intersect_vert_y;
	double	distance;
	double	hit_x;
	double	hit_y;
	int		hit_vertical;
	int		map_x;
	int		map_y;
	double	ray_angle;
	int		is_active;
}	t_ray;

typedef struct s_minimap
{
	int				map_width;
	int				map_height;
	int				player_grid_x;
	int				player_grid_y;
	char			nswe;
	char			**map;
}	t_minimap;

typedef struct s_vector
{
	double			x;
	double			y;
}	t_vector;

typedef struct s_player
{
	t_vector		pos;
	t_vector		dir;
	t_vector		plane;
	t_vector		move;
	t_vector		next_pos;
	double			radians;
	double			fov_in_radians;
	double			rot_speed;
}	t_player;

typedef struct s_struct
{
	int				fd;
	int				player_x;
	int				player_y;
	int				screen_width;
	int				screen_height;
	t_minimap		minimap;
	t_texture		texture;
	t_texture_data	texdata;
	t_player		player;
	t_ray			*ray;
	mlx_t			*mlx_ptr;
	mlx_image_t		*minimap_img;
	mlx_image_t		*main_img;
}	t_struct;

void			init_minimap(t_minimap *map_struct);
void			init_textures(t_struct *game_struct);
void			init_player(t_struct *game_struct);
void			init_raycast(t_struct *game_struct);
void			init_player_direction(t_player *player, char nswe);
void			items_controller(t_struct *game_struct);
void			draw_controller(t_struct *game_struct);
void			error_controller(t_struct *game_struct, int error_id);
void			map_controller(t_struct *game_struct);
void			loop_controller(void *param);
void			raycast_controller(t_struct *game_struct); //cast_rays
void			draw_map(mlx_image_t *img, t_struct *game_struct);
void			draw_map_with_config(mlx_image_t *img, t_struct *game_struct);
void			draw_tile(mlx_image_t *img, int x, int y, uint32_t color);
void			draw_player_square(t_struct *game_struct, mlx_image_t *img);
int				draw_new_image(t_struct *game_struct);
void			draw_roof(t_struct *game, int top_pixel, int ray);
void			draw_floor(t_struct *game, int bottom_pixel, int ray);
void			draw_textured_wall(t_struct *game_struct, 
					double wall_height, int top_pixel, int bottom_pixel);
void			draw_wall_plain_colors(t_struct *game_struct,
					int t_pix, int b_pix);
void			draw_wall_strip(t_struct *game_data, int top_pixel,
					int bottom_pixel, double texture_x, double texture_y,
						double scale_factor, mlx_texture_t *texture,
							uint32_t *texture_pixels);
void			draw_green_ray(t_struct *game_struct, double angle);
void			draw_rays_on_minimap(t_struct *game, t_ray ray);
void			draw_all_green_rays(t_struct *game_struct);
void			draw_direction_line(t_struct *game_struct);
void			draw_minimap_grid(t_struct *game_struct);
void			draw_wall_column(int column, t_struct *game);
void			draw_game_pixel(t_struct *game, int x, int y, int color); 
void			flood_fill(int y, int x, t_struct *game_struct);
int				calc_wall_bounds(double distance, double *top,
					double *bottom, int fov_rad);
bool			rotate_player(t_struct *game_struct, int key);
double			normalize_angle(double angle);
void			normalize_movement(t_struct *game_struct);
void			handle_movement_keys(t_struct *game_struct);
void			ft_player_movement(t_struct *game_struct);
void			ft_keyboard(void *param);
uint32_t 		swap_bytes_order(uint32_t val); //reverse_bytes
int				detect_hit_wall(t_struct *game_struct, float x, float y);
double			get_texture_x_offset(t_struct *game, mlx_texture_t *texture); // get_x_o
uint32_t 		*get_texture_pixels(mlx_texture_t *texture);
void			init_horizontal_intersection(float angle, 
					t_struct *game_struct, float *intersect_x, 
						float *intersect_y, float *step_x, float *step_y, 
							int *pixel_offset);
void			init_vertical_intersection(float angle,
					t_struct *game_struct,
						float *intersect_x, float *intersect_y, 
							float *step_x, float *step_y, int *pixel_offset);
float			calculate_vertical_ray_hit(float angle, t_struct *game_struct);
float			calculate_horizontal_ray_hit(float angle, t_struct *game);
double 			calculate_texture_y_offset(double wall_height, int top_pixel);
int				get_rgba(int r, int g, int b, int a);
double			get_corrected_distance(t_struct *game_struct);
int				ray_facing_up_or_left(char axis, float angle); //unit_circle
int				ray_intersection(float *coord, int is_horizontal,
					 float *step, float angle); //inter_check
void			load_file(t_struct *game_struct, char *file_path);
void			load_textures(t_struct *game_struct);
void			process_map_file_lines(t_struct *game_struct);
mlx_texture_t	*get_texture(t_struct *game_struct, int hit_type);
mlx_texture_t	*get_horizontal_texture(t_struct *game_struct);
mlx_texture_t	*get_vertical_texture(t_struct *game_struct);
uint32_t		rgb_to_hex(char *rgb_tab);
bool			check_extension(char *map_path, char *extension);
int				verify_file_integrity(t_struct *game_struct,
					char *file_path, char *filetype);
void			free_split(char **split);
void			free_graphics(t_struct *game_struct);
void			free_game_data(t_struct *game_struct);
bool			parse_rgb(char *str, int *rgb);
void			parse_texture_line(t_texture_data *texdata,
					char *line, t_struct *game_struct);
void			parse_player_spawn_position(t_struct *game_struct, char **map);
void			init_game(t_struct *game_struct);
void			map_free(char **map);
int				map_width(char *line);
void			exit_game(t_struct *game_struct);
int				new_window(t_struct *game_struct);
void			clear_textures(t_texture *texture);
void			restore_map(t_struct *game_struct);
int				parse_map(t_struct *game_struct, char *line);
char			*parse_texture_path(int del, char *line);
int				check_if_all_textures_loaded(t_texture_data *texdata);
bool			is_walkable(t_struct *game_struct, int y, int x);
int				is_valid_map_char(char c);
int				is_valid_rgb(const char *str);
void			validate_map_chars(t_struct *game_struct);
int				validate_textures(t_texture_data *texts_info, t_struct *game);
const			char *error_messages_list[ERRMAX];

//hooks
void			hooks(t_struct *game_struct);

//UTILS FOR DEBBUGING
void			print_map_on_console(t_struct *game_struct);
void			player_current_grid_pos(t_minimap *map);
void			draw_degub_green_line_direction(t_struct *game_struct);

//get next line
size_t	ft_strlen(const char *str);
char	*get_next_line(int fd);
char	*ft_readed_line(char *src);
char	*ft_strchr(const char *s, int c);
char	*ft_move_start(char *start);

//printf
int		ft_printf(const char *str, ...);
int		ft_printchar(char c);
int		ft_printdigit(long n, int base, int uppercase);
int		ft_printptr(unsigned long long ptr);
int		ft_printstr(char *str);

#endif