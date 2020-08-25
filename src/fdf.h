/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:33:08 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/25 13:38:38 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"
# include "ft_printf.h"

/*
** KEYBOARD EVENTS
*/

# define ESC		53

typedef enum		e_opt
{
	e_leaks = 0x01
}					t_opt;

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

typedef struct		s_line
{
	t_vec3			start_pos;
	t_vec3			end_pos;
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
}					t_input;

typedef struct		s_fdf_data
{
	t_input				*input;
	void				*mlx_ptr;
	t_window			window;
	void				*win_ptr;
	t_mlx_image_data	*line_img_data;
}					t_fdf_data;

int					keyboard_event(int key, void *fdf_data);
int					mouse_key_event(int button, int x, int y, void *fdf_data);
int					mouse_wheel_event(int x, int y, void *fdf_data);
int					close_window_event(void *fdf_data);
t_mlx_image_data	*create_line_image(int width, int hight, void *mlx_ptr);
void				update_line_image(t_mlx_image_data *line_img_data,
												void *mlx_ptr, void *win_ptr);
void				read_opt(t_input *input, int *argc, char ***argv);
void				bresenham_draw_line(t_mlx_image_data *line_img_data);

#endif
