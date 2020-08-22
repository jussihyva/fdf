/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 20:10:51 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/22 12:19:26 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			keyboard_event(int key, void *screen_data)
{
	t_win_ptr	*win_ptr;

	win_ptr = (t_win_ptr *)screen_data;
	ft_printf("%d\n", key);
	return (1);
}

int			mouse_key_event(int button, int x, int y, void *screen_data)
{
	t_win_ptr	*win_ptr;

	(void)x;
	(void)y;
	win_ptr = (t_win_ptr *)screen_data;
	ft_printf("%d\n", button);
	return (1);
}

int			mouse_wheel_event(int x, int y, void *screen_data)
{
	t_win_ptr	*win_ptr;

	(void)x;
	(void)y;
	win_ptr = (t_win_ptr *)screen_data;
	ft_printf("%s\n", "J");
	return (1);
}

int			close_window_event(void *screen_data)
{
	t_win_ptr	*win_ptr;

	win_ptr = (t_win_ptr *)screen_data;
	ft_printf("Request to exit.\n");
	exit(0);
}
