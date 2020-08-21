/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 20:10:51 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/21 21:08:47 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int			keyboard_event(int key, void *screen_data)
{
	t_win_ptr	*win_ptr;

	win_ptr = (t_win_ptr *)screen_data;
	if (key == 124)
		printf("pressed right\n");
	draw_line(win_ptr);
	return (1);
}

int			mouse_key_event(int button, int x, int y, void *screen_data)
{
	t_win_ptr	*win_ptr;

	(void)x;
	(void)y;
	win_ptr = (t_win_ptr *)screen_data;
	if (button == 124)
		printf("pressed right\n");
	draw_line(win_ptr);
	return (1);
}

int			mouse_wheel_event(int x, int y, void *screen_data)
{
	t_win_ptr	*win_ptr;

	(void)x;
	(void)y;
	win_ptr = (t_win_ptr *)screen_data;
	if (x == 124)
		printf("pressed right\n");
	draw_line(win_ptr);
	return (1);
}
