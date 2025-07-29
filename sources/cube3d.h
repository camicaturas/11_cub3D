/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:12:05 by ohosnedl          #+#    #+#             */
/*   Updated: 2025/07/08 15:25:57 by cberneri         ###   ########.fr       */
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
# define SHOW_ITEMS_IN_MAP		0

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
	int				player_grid_x; //for Center the minimap around the player
	int				player_grid_y; //for Center the minimap around the player
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
	t_vector		pos;			// 	Current player position in the world (x, y).
	t_vector		dir;			// Direction vector the player is facing. Important for raycasting.
	t_vector		plane;			// 2D camera plane (perpendicular to dir). Determines how the view is projected.
	t_vector		move;			// store intended movement direction
	t_vector		next_pos;		// Next position for calculation
	double			radians;		// Angle in radians (optional use)
	double			fov_in_radians;	// Field of view in radians (e.g. 60° → π/3). Determines how wide the player sees.
	double			rot_speed;		//How fast the player rotates (radians per frame).
}	t_player;


//// ITEMS
/*
# define MAX_SPRITES 128 // FOR ITEMS check LATER IF IT WORKS OR DELETE IT

typedef struct s_sprite {
	double x;
	double y;
	double distance; // squared distance to player
}	t_sprite;

typedef struct s_item {
	t_sprite		sprites[MAX_SPRITES];
	int				count;
	mlx_texture_t	*texture_item;
}	t_item;
*/
///////////// END OF ITEMS


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
	//t_item			item;  	//for ITEMS
	mlx_t			*mlx_ptr;
	mlx_image_t		*minimap_img;
	mlx_image_t		*main_img;
	//double			zbuffer[WINDOW_WIDTH]; 	//for ITEMS
}	t_struct;

void			init_minimap(t_minimap *map_struct);
void			init_textures(t_struct *game_struct);
void			init_player(t_struct *game_struct);
void			init_raycast(t_struct *game_struct);
void			init_player_direction(t_player *player, char nswe);
void			items_controller(t_struct *game_struct);
void			draw_controller(t_struct *game_struct);
void			draw_map(mlx_image_t *img, t_struct *game_struct);
void			draw_map_with_config(mlx_image_t *img, t_struct *game_struct);
void			draw_tile(mlx_image_t *img, int x, int y, uint32_t color);
void			draw_player_square(t_struct *game_struct, mlx_image_t *img);
int				draw_new_image(t_struct *game_struct);
void			draw_roof(t_struct *game, int top_pixel, int ray);
void			draw_floor(t_struct *game, int bottom_pixel, int ray);
void			draw_textured_wall(t_struct *game_struct, 
					double wall_height, int top_pixel, int bottom_pixel);
void			draw_wall_plain_colors(t_struct *game_struct, int t_pix, int b_pix);
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
int				calc_wall_bounds(double distance, double *top,
					double *bottom, int fov_rad);
void			loop_controller(void *param);
bool			is_walkable(t_struct *game_struct, int y, int x);
bool			rotate_player(t_struct *game_struct, int key);
double			normalize_angle(double angle);
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
void			raycast_controller(t_struct *game_struct); //cast_rays
int				ray_facing_up_or_left(char axis, float angle); //unit_circle
int				ray_intersection(float *coord, int is_horizontal,
					 float *step, float angle); //inter_check
void			load_file(t_struct *game_struct, char *file_path);
void			load_textures(t_struct *game_struct);
mlx_texture_t	*get_texture(t_struct *game_struct, int hit_type);
mlx_texture_t	*get_horizontal_texture(t_struct *game_struct);
mlx_texture_t	*get_vertical_texture(t_struct *game_struct);
uint32_t		rgb_to_hex(char *rgb_tab);
int				check_rgb(int *rgb);
int				check_textures(t_struct *game, t_texture_data *textures);
void			free_split(char **split);
void			parse_rgb(char *str, int *rgb);
void			parse_texture_line(t_texture_data *texdata, char *line, t_struct *game_struct);
void			parse_player_spawn_position(t_struct *game_struct, char **map);
void			init_game(t_struct *game_struct);
void			map_free(char **map);
int				map_width(char *line);
int				check_extension(char *map_path);
void			exit_more_map_error(t_struct *game_struct, int num);
void			exit_game_error(t_struct *game_struct, int num);
void			exit_game(t_struct *game_struct);
int				new_window(t_struct *game_struct);
//void			render_item(t_struct *g); // for ITEMS

//hooks
void			hooks(t_struct *game_struct);

//UTILS FOR DEBBUGING
void			print_map_on_console(t_struct *game_struct);
void			player_current_grid_pos(t_minimap *map);
void			draw_degub_green_line_direction(t_struct *game_struct);



 
/*
//OLD SO_LONG FUNCTIONS (CAN BE DELETED WHEN THE PROJECT IS DONE)
int		check_borders(t_struct *game_struct);
int		check_counts(t_struct *game_struct);
int		check_exit(t_struct *game_struct);
int		check_player_spawn(t_struct *game_struct);
int		check_count_collectibles(t_struct *game_struct);
void	check_map(t_struct *game_struct);
int		check_map_shape(t_struct *game_struct);
void	exit_map_error(t_struct *game_struct, int num);
void	flood_fill(int y, int x, t_struct *game_struct);
void	flood_fill_check(t_struct *game_struct, int y, int x);
void	ft_movement_y(t_struct *game_struct, char direction);
void	ft_movement_x(t_struct *game_struct, char direction);
int		map_valid(t_struct *game_struct);
char	**player_current_position(t_struct *game_struct);
*/


//get next line
size_t	ft_strlen(const char *str);
char	*get_next_line(int fd);
char	*ft_readed_line(char *src);
char	*ft_strchr(const char *s, int c);
char	*ft_move_start(char *start);
//char	*ft_strjoin(char *s1, char *s2);

//printf
int		ft_printf(const char *str, ...);
int		ft_printchar(char c);
int		ft_printdigit(long n, int base, int uppercase);
int		ft_printptr(unsigned long long ptr);
int		ft_printstr(char *str);

#endif