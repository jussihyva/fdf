/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 16:19:56 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/27 15:59:53 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		draw_low(t_mlx_image_data *img_data,
													t_drawing_data drawing_data)
{
	t_vec2	delta;
	int		difference;
	t_vec2	plot_pos;
	int		step;

	delta.x = ft_abs(drawing_data.end_pos.x - drawing_data.start_pos.x);
	delta.y = ft_abs(drawing_data.end_pos.y - drawing_data.start_pos.y);
	difference = 2 * delta.y - delta.x;
	step = (drawing_data.end_pos.y < drawing_data.start_pos.y) ? -1 : 1;
	plot_pos.y = drawing_data.start_pos.y;
	plot_pos.x = drawing_data.start_pos.x;
	while (plot_pos.x <= drawing_data.end_pos.x)
	{
		img_data->img_buffer[(plot_pos.y * drawing_data.ints_in_image_line) +
											plot_pos.x] = img_data->line.color;
		if (difference > 0)
		{
			plot_pos.y += step;
			difference -= (2 * delta.x);
		}
		difference += (2 * delta.y);
		plot_pos.x++;
	}
	return ;
}

static void		draw_high(t_mlx_image_data *img_data,
													t_drawing_data drawing_data)
{
	t_vec2	delta;
	int		difference;
	t_vec2	plot_pos;
	int		step;

	delta.x = ft_abs(drawing_data.end_pos.x - drawing_data.start_pos.x);
	delta.y = ft_abs(drawing_data.end_pos.y - drawing_data.start_pos.y);
	difference = 2 * delta.x - delta.y;
	step = (drawing_data.end_pos.x < drawing_data.start_pos.x) ? -1 : 1;
	plot_pos.y = drawing_data.start_pos.y;
	plot_pos.x = drawing_data.start_pos.x;
	while (plot_pos.y <= drawing_data.end_pos.y)
	{
		img_data->img_buffer[(plot_pos.y * drawing_data.ints_in_image_line) +
											plot_pos.x] = img_data->line.color;
		if (difference > 0)
		{
			plot_pos.x += step;
			difference -= (2 * delta.y);
		}
		difference += (2 * delta.x);
		plot_pos.y++;
	}
	return ;
}

void			bresenham_draw_line(t_mlx_image_data *img_data, t_line line)
{
	int				delta_x;
	int				delta_y;
	t_drawing_data	drawing_data;

	drawing_data.color = line.color;
	drawing_data.ints_in_image_line = img_data->line_bytes / 4;
	delta_x = ft_abs(line.end_pos.x - line.start_pos.x);
	delta_y = ft_abs(line.end_pos.y - line.start_pos.y);
	if ((delta_y < delta_x && line.start_pos.x > line.end_pos.x) ||
		(delta_y > delta_x && line.start_pos.y > line.end_pos.y))
	{
		drawing_data.start_pos = line.end_pos;
		drawing_data.end_pos = line.start_pos;
	}
	else
	{
		drawing_data.start_pos = line.start_pos;
		drawing_data.end_pos = line.end_pos;
	}
	if (delta_y < delta_x)
		draw_low(img_data, drawing_data);
	else
		draw_high(img_data, drawing_data);
	return ;
}
