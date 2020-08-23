/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 20:10:51 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/23 12:36:13 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			keyboard_event(int key, void *fdf_data)
{
	(void)fdf_data;
	if (key == ESC)
	{
		ft_printf("Request (ESC key pressed) to exit.\n");
		exit(0);
	}
	else
		ft_printf("%d\n", key);
	return (1);
}

int			mouse_key_event(int button, int x, int y, void *fdf_data)
{
	(void)x;
	(void)y;
	(void)fdf_data;
	ft_printf("%d\n", button);
	return (1);
}

int			mouse_wheel_event(int x, int y, void *fdf_data)
{
	(void)x;
	(void)y;
	(void)fdf_data;
	return (1);
}

int			close_window_event(void *fdf_data)
{
	(void)fdf_data;
	ft_printf("Request to exit.\n");
	exit(0);
}
