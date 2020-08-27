/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 16:19:56 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/27 14:18:22 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		draw_low(t_mlx_image_data *line_img_data, t_vec3 start_pos,
										t_vec3 end_pos, int integers_in_line)
{
	t_vec2	delta;
	int		difference;
	t_vec2	plot_pos;
	int		step;

	delta.x = ft_abs(end_pos.x - start_pos.x);
	delta.y = ft_abs(end_pos.y - start_pos.y);
	difference = 2 * delta.y - delta.x;
	step = (end_pos.y < start_pos.y) ? -1 : 1;
	plot_pos.y = start_pos.y;
	plot_pos.x = start_pos.x;
	while (plot_pos.x <= end_pos.x)
	{
		line_img_data->img_buffer[(plot_pos.y * integers_in_line) +
										plot_pos.x] = line_img_data->line.color;
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

static void		draw_high(t_mlx_image_data *line_img_data, t_vec3 start_pos,
										t_vec3 end_pos, int integers_in_line)
{
	t_vec2	delta;
	int		difference;
	t_vec2	plot_pos;
	int		step;

	delta.x = ft_abs(end_pos.x - start_pos.x);
	delta.y = ft_abs(end_pos.y - start_pos.y);
	difference = 2 * delta.x - delta.y;
	step = (end_pos.x < start_pos.x) ? -1 : 1;
	plot_pos.y = start_pos.y;
	plot_pos.x = start_pos.x;
	while (plot_pos.y <= end_pos.y)
	{
		line_img_data->img_buffer[(plot_pos.y * integers_in_line) +
										plot_pos.x] = line_img_data->line.color;
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

void			bresenham_draw_line(t_mlx_image_data *line_img_data, t_line line)
{
	int		delta_x;
	int		delta_y;
	int		int_lines;

	int_lines = line_img_data->line_bytes / 4;
	delta_x = ft_abs(line.end_pos.x - line.start_pos.x);
	delta_y = ft_abs(line.end_pos.y - line.start_pos.y);
	if (delta_y < delta_x)
	{
		if (line.start_pos.x > line.end_pos.x)
			draw_low(line_img_data, line.end_pos, line.start_pos, int_lines);
		else
			draw_low(line_img_data, line.start_pos, line.end_pos, int_lines);
	}
	else
	{
		if (line.start_pos.y > line.end_pos.y)
			draw_high(line_img_data, line.end_pos, line.start_pos, int_lines);
		else
			draw_high(line_img_data, line.start_pos, line.end_pos, int_lines);
	}
	return ;
}
