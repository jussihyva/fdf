/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:33:08 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/21 21:03:06 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"

typedef struct	s_win_ptr
{
	void		*mlx_ptr;
	void		*win_ptr;
}				t_win_ptr;

void			draw_line(t_win_ptr *screen_data);
int				keyboard_event(int key, void *screen_data);
int				mouse_key_event(int button, int x, int y, void *screen_data);
int				mouse_wheel_event(int x, int y, void *screen_data);

#endif
