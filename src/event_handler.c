/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 20:10:51 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/27 17:12:57 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_event_order	validate_order_type(int key, t_fdf_data *fdf_data)
{
	t_event_order	event_order;

	if (key == ESC)
	{
		ft_printf("Request (ESC key pressed) to exit.\n");
		event_order = e_close_window;
	}
	else if (fdf_data->input->opt & e_test)
		event_order = validate_test_orders(key, fdf_data);
	else
		event_order = e_none;
	return (event_order);
}

int						keyboard_event(int key, void *param)
{
	t_fdf_data		*fdf_data;
	t_event_order	event_order;

	fdf_data = (t_fdf_data *)param;
	event_order = validate_order_type(key, fdf_data);
	if (event_order == e_close_window)
		close_window_event(fdf_data);
	else if (event_order == e_update_line_img)
		update_line_image(fdf_data->line_img_data, fdf_data->mlx_ptr,
															fdf_data->win_ptr);
	else
		ft_printf("%d\n", key);
	return (0);
}

int						mouse_key_event(int button, int x, int y, void *param)
{
	t_fdf_data		*fdf_data;

	(void)x;
	(void)y;
	fdf_data = (t_fdf_data *)param;
	ft_printf("%d\n", button);
	return (0);
}

int						mouse_wheel_event(int x, int y, void *param)
{
	t_fdf_data		*fdf_data;

	fdf_data = (t_fdf_data *)param;
	if (x >= 0 && y >= 0 && x < fdf_data->window.width &&
													y < fdf_data->window.hight)
	{
		fdf_data->line_img_data->line.end_pos.x = x;
		fdf_data->line_img_data->line.end_pos.y = y;
		update_line_image(fdf_data->line_img_data, fdf_data->mlx_ptr,
															fdf_data->win_ptr);
	}
	else
		mlx_clear_window(fdf_data->mlx_ptr, fdf_data->win_ptr);
	return (0);
}

int						close_window_event(void *param)
{
	t_fdf_data		*fdf_data;

	fdf_data = (t_fdf_data *)param;
	ft_printf("Request to exit.\n");
	if (fdf_data->input->opt & e_leaks)
		system("leaks fdf");
	exit(0);
}
