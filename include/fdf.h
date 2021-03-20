/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 10:30:23 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/20 22:02:15 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"
# include "libft_addons.h"
# include "ft_printf.h"
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define NUM_OF_ELEM_POSITIONS		8
# define NUM_OF_OBJECT_POSITIONS	8

double	**g_z_rotation_matrix[360];
int		g_z_is_rotation_matrix[360];
double	**g_y_rotation_matrix[360];
int		g_y_is_rotation_matrix[360];
double	**g_x_rotation_matrix[360];
int		g_x_is_rotation_matrix[360];

typedef enum	e_event_type
{
	LOG_TRACE = 0,
	LOG_DEBUG = 1,
	LOG_INFO = 2,
	LOG_WARN = 3,
	LOG_ERROR = 4,
	LOG_FATAL = 5
}				t_event_type;

typedef struct	s_cmd_args
{
	char			*map_file;
	size_t			projection_type;
	int				x;
	int				y;
	int				z;
	int				elem_side_len;
	int				altitude_factor;
	int				angle_steps;
	t_event_type	loging_level;
}				t_cmd_args;

typedef struct	s_xyz_values
{
	double		x;
	double		y;
	double		z;
}				t_xyz_values;

typedef struct	s_xy_values
{
	double		x;
	double		y;
}				t_xy_values;

typedef struct	s_xy_values_int
{
	int			x;
	int			y;
}				t_xy_values_int;

typedef struct	s_xy_values_old
{
	int			x;
	int			y;
}				t_xy_values_old;

typedef struct	s_object_type
{
	t_xyz_values	size;
	t_xyz_values	angle;
	t_xyz_values	*start_positions;
	t_xyz_values	*current_positions;
}				t_object_type;

typedef struct	s_map
{
	int					**elem_altitude;
	int					**elem_color;
	int					colors_from_map_file;
	int					max_altitude;
	int					min_altitude;
	size_t				obj_counter;
	t_xy_values_old		*map_size;
	t_object_type		***object_type;
}				t_map;

typedef struct	s_position
{
	int			x;
	int			y;
	int			z;
}				t_position;

typedef struct	s_position_new
{
	double		x;
	double		y;
	double		z;
}				t_position_new;

typedef struct	s_input
{
	const char			**level_strings;
	const char			**level_colors;
	t_cmd_args			*cmd_args;
	t_map				*map;
	t_xyz_values		*angle;
	t_xy_values			object_xy_size;
}				t_input;

typedef enum	e_render_action
{
	e_no_action,
	e_put_image_to_window
}				t_render_action;

typedef struct	s_elem_size
{
	int			x;
	int			y;
	int			z;
}				t_elem_size;

typedef struct	s_elem_line
{
	t_xyz_values		*start;
	t_xyz_values		*end;
	int					color;
	int					line_type;
}				t_elem_line;

typedef struct	s_drawing_data
{
	unsigned int		color;
	int					size_line;
	t_xy_values_int		start;
	t_xy_values_int		end;
	int					line_type;
}				t_drawing_data;

typedef struct	s_element
{
	t_object_type	*object_type;
	t_xyz_values	*angle;
	int				color;
	t_position		elem_position_offset;
	t_elem_line		*elem_lines;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	t_xyz_values	*start_position;
}				t_element;

typedef struct	s_mlx_win
{
	void				*mlx;
	void				*win;
	t_list				**object_type_lst;
	t_element			***elem_table;
	t_position			*first_elem_start_position;
	t_element			***element_map;
	t_xy_values_old		*element_map_size;
	t_xyz_values		*angle;
	double				angle_step;
	t_img				*img;
	t_position			*img_start_position;
	t_xyz_values		*img_position_offset;
	t_img				*empty_img;
	t_xy_values_old		img_size;
	t_render_action		render_action;
}				t_mlx_win;

int				close_win(t_mlx_win *mlx_win);
int				button_press(int keycode, int x, int y, t_mlx_win *mlx_win);
int				key_press(int keycode, t_mlx_win *mlx_win);
int				motion_notify(int x, int y, t_mlx_win *mlx_win);
int				enter_notify(t_mlx_win *mlx_win);
int				leave_notify(t_mlx_win *mlx_win);
void			release_mlx_win(t_mlx_win **mlx_win);
int				render_frame(t_mlx_win *mlx_win);
t_element		*create_element(t_mlx_win *mlx_win,
					t_xyz_values *start_position, t_xyz_values *position_offset,
													t_object_type *object_type);
void			mlx_image_pixel_put(t_img *img, int x, int y, int color);
void			initialize_window(t_mlx_win *mlx_win, char *window_name);
t_xyz_values	*set_elem_positions(t_xyz_values *elem_size);
void			elemental_rotation(t_xyz_values *current_positions,
							t_xyz_values *angle, t_xyz_values *position_offset,
												t_xyz_values *start_position);
void			draw_lines(t_img *img, t_element *element);
void			set_position(t_xyz_values *position, double x, double y,
																	double z);
t_input			*read_cmd_arguments(int argc, char **argv);
void			bresenham_draw_line(t_img *img, t_elem_line *line,
											t_position *elem_position_offset);
void			release_input_data(t_input **input);
t_cmd_args		*argp_parse(int argc, char **argv,
											void (fn)(t_cmd_args *, char, char *));
void			print_start_position(t_position *elem_start_position);
void			create_object_types(t_list **object_type_lst, t_map *map,
																t_input *input);
void			rotate(t_xyz_values *elem_position, t_xyz_values *angle);
void			rotate_objects(t_list **object_type_lst, t_xyz_values *angle);
void			save_cmd_arguments(t_cmd_args *cmd_args, char opt,
																char *next_arg);
void			create_elements(t_map *map, t_element ***elem_table,
															t_mlx_win *mlx_win);

# include <time.h>
# include <sys/time.h>

# define MAX_LOGING_EXTENSIONS 32

typedef struct	s_log_event
{
	va_list			ap;
	const char		*fmt;
	const char		*file;
	struct timeval	tv;
	int				fd;
	int				line;
	int				level;
}				t_log_event;

typedef void (*loging_function)(t_log_event *event);
typedef void (*loging_lock_function)(int lock, void *udata);

typedef struct	s_loging_extension
{
	loging_function		fn;
	int					fd;
	int					level;
}				t_loging_extension;

typedef struct	s_loging_params
{
	void					*udata;
	loging_lock_function	lock;
	int						level;
	int						quiet;
	const char				**level_strings;
	const char				**level_colors;
	t_loging_extension		*loging_extensions[MAX_LOGING_EXTENSIONS];
}				t_loging_params;

# define ft_log_trace(...) ft_login_event(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
# define ft_log_debug(...) ft_login_event(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
# define ft_log_info(...)  ft_login_event(LOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
# define ft_log_warn(...)  ft_login_event(LOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
# define ft_log_error(...) ft_login_event(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
# define ft_log_fatal(...) ft_login_event(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

void			ft_log_set_lock(loging_lock_function fn, void *udata);
void			ft_log_set_level(int level);
// void			log_set_quiet(int enable);
// int				log_add_callback(loging_function fn, void *udata, int level);
int				ft_log_add_fp(int fd, int level);
void			ft_login_event(int level, const char *file, int line,
														const char *fmt, ...);
void			ft_log_set_params(const char **level_strings,
													const char **level_colors);

#endif
