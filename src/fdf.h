/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:33:08 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/27 17:13:20 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include <fcntl.h>
# include "libft.h"
# include "ft_printf.h"

/*
** VALUES FOR INPUT DATA ANALYSIS
*/

# define NUM_OF_ERROR_STRINGS		10
# define MAX_NUM_OF_LINES			1000
# define MAP_FILE_PARAM_DELIMITER	' '
# define WINDOW_WIDTH				900
# define WINDOW_HIGHT				600

/*
** KEYBOARD EVENTS
*/

# define ESC		53

typedef enum		e_opt
{
	e_leaks = 0x01,
	e_map_file = 0x02,
	e_test = 0x04
}					t_opt;

typedef enum		e_error
{
	e_input_file_missing = 1,
	e_file_open_failure,
	e_input_file_parse_error
}					t_error;

typedef enum		e_event_order
{
	e_none,
	e_close_window,
	e_update_line_img
}					t_event_order;

typedef struct		s_vec2
{
	int				x;
	int				y;
}					t_vec2;

typedef struct		s_vec3
{
	int				x;
	int				y;
	int				z;
}					t_vec3;

typedef struct		s_point
{
	int				altitude;
	int				color;
}					t_point;

typedef struct		s_line
{
	t_vec2			start_pos;
	t_vec2			end_pos;
	unsigned int	color;
}					t_line;

typedef struct		s_window
{
	int				width;
	int				hight;
}					t_window;

typedef struct		s_mlx_image_data
{
	int				width;
	int				hight;
	void			*img_ptr;
	int				*img_buffer;
	int				img_buffer_size;
	int				pixel_bits;
	int				line_bytes;
	int				endian;
	t_line			line;
}					t_mlx_image_data;

typedef struct		s_input
{
	t_opt			opt;
	t_error			error;
	char			**error_string;
	char			*input_file_path;
	int				input_array_size;
	int				width;
	int				hight;
	t_point			**point_array;
}					t_input;

typedef struct		s_fdf_data
{
	t_input				*input;
	void				*mlx_ptr;
	t_window			window;
	void				*win_ptr;
	t_mlx_image_data	*line_img_data;
}					t_fdf_data;

typedef struct		s_drawing_data
{
	t_vec2				start_pos;
	t_vec2				end_pos;
	unsigned int		color;
	int					step;
	int					ints_in_image_line;
}					t_drawing_data;

int					keyboard_event(int key, void *fdf_data);
int					mouse_key_event(int button, int x, int y, void *fdf_data);
int					mouse_wheel_event(int x, int y, void *fdf_data);
int					close_window_event(void *fdf_data);
t_mlx_image_data	*create_empty_image(t_window window, void *mlx_ptr);
t_mlx_image_data	*create_line_image(t_window window, void *mlx_ptr);
void				update_line_image(t_mlx_image_data *line_img_data,
												void *mlx_ptr, void *win_ptr);
void				read_opt(t_input *input, int *argc, char ***argv);
void				bresenham_draw_line(t_mlx_image_data *line_img_data,
																t_line line);
t_input				*read_command_attributes(int argc, char **argv);
void				save_input_file(t_input *input, int *argc, char ***argv);
t_point				*parse_map_line(char *line, int *array_size,
																t_error *error);
void				read_map_file(t_input *input, void *img_data);
void				add_line_to_image(t_mlx_image_data *img_data,
							t_point *point_array, int line_cnt, int array_size);
t_event_order		validate_test_orders(int key, t_fdf_data *fdf_data);

#endif
