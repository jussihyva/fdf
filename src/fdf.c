/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:32:32 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/22 12:14:45 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			main(void)
{
	t_win_ptr	win1_ptr;
	int			win1_width;
	int			win1_length;

	win1_width = 2000;
	win1_length = 1000;
	win1_ptr.mlx_ptr = mlx_init();
	win1_ptr.win_ptr = mlx_new_window(win1_ptr.mlx_ptr, win1_width,
														win1_length, "MOI!");
	mlx_key_hook(win1_ptr.win_ptr, &keyboard_event, &win1_ptr);
	mlx_mouse_hook(win1_ptr.win_ptr, &mouse_key_event, &win1_ptr);
	mlx_hook(win1_ptr.win_ptr, 6, 0, &mouse_wheel_event, &win1_ptr);
	mlx_hook(win1_ptr.win_ptr, 17, 0, &close_window_event, &win1_ptr);
	draw_line(&win1_ptr);
	mlx_loop(win1_ptr.mlx_ptr);
	return (0);
}
