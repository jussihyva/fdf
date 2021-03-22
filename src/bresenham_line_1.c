/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_line_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 16:19:56 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/22 11:24:58 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		set_image_point(t_position *plot_pos,
						t_drawing_data *drawing_data, unsigned int *img_buffer)
{
	int				plot_index;

	plot_index = (plot_pos->y * drawing_data->size_line) + plot_pos->x;
	if (img_buffer[plot_index] < drawing_data->color)
	{
		if ((plot_pos->x / 2) % 2 || drawing_data->line_type == 0)
			img_buffer[plot_index] = drawing_data->color;
		else
			img_buffer[plot_index] = 0;
	}
	return ;
}

static void		draw_low(unsigned int *img_buffer,
								t_drawing_data *drawing_data, t_delta *delta)
{
	int				difference;
	t_position		plot_pos;
	int				step;

	difference = 2 * delta->y - delta->x;
	step = (drawing_data->end.y < drawing_data->start.y) ? -1 : 1;
	plot_pos.y = drawing_data->start.y;
	plot_pos.x = drawing_data->start.x;
	ft_log_trace("Drawing low line: Step=%d", step);
	while (plot_pos.x <= drawing_data->end.x)
	{
		set_image_point(&plot_pos, drawing_data, img_buffer);
		if (difference > 0)
		{
			plot_pos.y += step;
			difference -= (2 * delta->x);
		}
		difference += (2 * delta->y);
		plot_pos.x++;
	}
	return ;
}

static void		draw_high(unsigned int *img_buffer,
								t_drawing_data *drawing_data, t_delta *delta)
{
	int				difference;
	t_position		plot_pos;
	int				step;

	difference = 2 * delta->x - delta->y;
	step = (drawing_data->end.x < drawing_data->start.x) ? -1 : 1;
	plot_pos.y = drawing_data->start.y;
	plot_pos.x = drawing_data->start.x;
	while (plot_pos.y <= drawing_data->end.y)
	{
		set_image_point(&plot_pos, drawing_data, img_buffer);
		if (difference > 0)
		{
			plot_pos.x += step;
			difference -= (2 * delta->y);
		}
		difference += (2 * delta->x);
		plot_pos.y++;
	}
	return ;
}

void			bresenham_draw_line(t_mlx_win *mlx_win, t_elem_line *line)
{
	t_delta			delta;
	t_drawing_data	drawing_data;
	t_img			*img;
	int				low;

	img = mlx_win->img;
	drawing_data.color = line->color;
	drawing_data.line_type = line->line_type;
	drawing_data.size_line = img->size_line / 4;
	drawing_data.start.x = (int)(mlx_win->img_position_offset->x +
					line->start->x + line->start_elem->start_position->x + 0.5);
	drawing_data.start.y = (int)(mlx_win->img_position_offset->y +
					line->start->y + line->start_elem->start_position->y + 0.5);
	drawing_data.end.x = (int)(mlx_win->img_position_offset->x +
					line->end->x + line->end_elem->start_position->x + 0.5);
	drawing_data.end.y = (int)(mlx_win->img_position_offset->y +
					line->end->y + line->end_elem->start_position->y + 0.5);
	low = set_drawing_data(&drawing_data, &delta);
	ft_log_trace("%3d,%3d --> %3d,%3d (delta_y:%d < delta_x:%d",
				drawing_data.start.x, drawing_data.start.y, drawing_data.end.x,
										drawing_data.end.y, delta.y, delta.x);
	if (low && delta.x >= delta.y)
		draw_low((unsigned int *)img->data, &drawing_data, &delta);
	else
		draw_high((unsigned int *)img->data, &drawing_data, &delta);
}
