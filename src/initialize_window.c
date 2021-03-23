/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 03:57:26 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/24 00:16:29 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		initialize_window(t_mlx_win *mlx_win, char *window_name)
{
	mlx_win->win = mlx_new_window(mlx_win->mlx, mlx_win->img_size.x,
											mlx_win->img_size.y, window_name);
	mlx_hook(mlx_win->win, 2, 0x01, key_press, mlx_win);
	mlx_hook(mlx_win->win, 4, 0x04, button_press, mlx_win);
	mlx_hook(mlx_win->win, 6, 0x40, motion_notify, mlx_win);
	mlx_hook(mlx_win->win, 7, 0x10, enter_notify, mlx_win);
	mlx_hook(mlx_win->win, 8, 0x20, leave_notify, mlx_win);
	mlx_hook(mlx_win->win, 33, 0x00, close_win, mlx_win);
	return ;
}
