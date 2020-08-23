/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:33:08 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/23 17:09:15 by jkauppi          ###   ########.fr       */
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

typedef struct		s_window
{
	int				width;
	int				hight;
}					t_window;

typedef struct		s_fdf_data
{
	void			*mlx_ptr;
	t_window		window;
	void			*win_ptr;
	void			*line_img;
}					t_fdf_data;

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
	t_vec3			current_pos;
}					t_line;

typedef enum		e_opt
{
	leaks = 0x01
}					t_opt;

typedef struct		s_input
{
	t_opt			opt;
}					t_input;

int					keyboard_event(int key, void *fdf_data);
int					mouse_key_event(int button, int x, int y, void *fdf_data);
int					mouse_wheel_event(int x, int y, void *fdf_data);
int					close_window_event(void *fdf_data);
void				*create_line_image(t_fdf_data *fdf_data, int x, int y);
void				read_opt(t_input *input, int *argc, char ***argv);
void				bresenham_draw_line_1(int *buffer, t_line *line,
															int line_length);

#endif
