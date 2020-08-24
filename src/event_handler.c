/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 20:10:51 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/24 21:33:26 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		close_window(void)
{
	system("leaks fdf");
	exit(0);
}

int				keyboard_event(int key, void *param)
{
	t_fdf_data		*fdf_data;

	fdf_data = (t_fdf_data *)param;
	if (key == ESC)
	{
		ft_printf("Request (ESC key pressed) to exit.\n");
		close_window();
	}
	else if (key == 123 && fdf_data->line.end_pos.x)
	{
		fdf_data->line.end_pos.x--;
		create_line_image(fdf_data, fdf_data->line.end_pos.x,
												fdf_data->line.end_pos.y);
	}
	else if (key == 124 && fdf_data->line.end_pos.x <
													fdf_data->window.width - 1)
	{
		fdf_data->line.end_pos.x++;
		create_line_image(fdf_data, fdf_data->line.end_pos.x,
												fdf_data->line.end_pos.y);
	}
	else if (key == 126 && fdf_data->line.end_pos.y)
	{
		fdf_data->line.end_pos.y--;
		create_line_image(fdf_data, fdf_data->line.end_pos.x,
												fdf_data->line.end_pos.y);
	}
	else if (key == 125 && fdf_data->line.end_pos.y <
													fdf_data->window.hight - 1)
	{
		fdf_data->line.end_pos.y++;
		create_line_image(fdf_data, fdf_data->line.end_pos.x,
												fdf_data->line.end_pos.y);
	}
	else
		ft_printf("%d\n", key);
	return (0);
}

int				mouse_key_event(int button, int x, int y, void *param)
{
	t_fdf_data		*fdf_data;

	(void)x;
	(void)y;
	fdf_data = (t_fdf_data *)param;
	ft_printf("%d\n", button);
	return (0);
}

int				mouse_wheel_event(int x, int y, void *param)
{
	t_fdf_data		*fdf_data;

	fdf_data = (t_fdf_data *)param;
	if (fdf_data->line_img)
	{
		mlx_destroy_image(fdf_data->mlx_ptr, fdf_data->line_img);
		fdf_data->line_img = NULL;
	}
	if (x >= 0 && y >= 0 && x < fdf_data->window.width &&
													y < fdf_data->window.hight)
	{
		ft_printf("x:%d y:%d\n", fdf_data->window.width,
														fdf_data->window.hight);
		ft_printf("x:%d y:%d\n", x, y);
		create_line_image(fdf_data, x, y);
		mlx_clear_window(fdf_data->mlx_ptr, fdf_data->win_ptr);
		mlx_put_image_to_window(fdf_data->mlx_ptr, fdf_data->win_ptr,
													fdf_data->line_img, 0, 0);
	}
	else
		mlx_clear_window(fdf_data->mlx_ptr, fdf_data->win_ptr);
	return (0);
}

int				close_window_event(void *fdf_data)
{
	(void)fdf_data;
	ft_printf("Request to exit.\n");
	close_window();
	return (0);
}
