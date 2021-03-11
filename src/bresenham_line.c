/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 16:19:56 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/11 13:18:55 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		draw_low(unsigned int *img_buffer, t_drawing_data *drawing_data)
{
	t_elem_size		delta;
	int				difference;
	t_position		plot_pos;
	int				step;
	int				plot_index;

	delta.x = ft_abs(drawing_data->end.x - drawing_data->start.x);
	delta.y = ft_abs(drawing_data->end.y - drawing_data->start.y);
	difference = 2 * delta.y - delta.x;
	step = (drawing_data->end.y < drawing_data->start.y) ? -1 : 1;
	plot_pos.y = drawing_data->start.y;
	plot_pos.x = drawing_data->start.x;
	while (plot_pos.x <= drawing_data->end.x)
	{
		plot_index = (plot_pos.y * drawing_data->size_line) + plot_pos.x;
		if (img_buffer[plot_index] < drawing_data->color)
		{
			if ((plot_pos.x / 2) % 2 || drawing_data->line_type == 0)
				img_buffer[plot_index] = drawing_data->color;
			else
				img_buffer[plot_index] = 0;
		}
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

static void		draw_high(unsigned int *img_buffer, t_drawing_data *drawing_data)
{
	t_elem_size		delta;
	int				difference;
	t_position		plot_pos;
	int				step;
	int				plot_index;

	delta.x = ft_abs(drawing_data->end.x - drawing_data->start.x);
	delta.y = ft_abs(drawing_data->end.y - drawing_data->start.y);
	difference = 2 * delta.x - delta.y;
	step = (drawing_data->end.x < drawing_data->start.x) ? -1 : 1;
	plot_pos.y = drawing_data->start.y;
	plot_pos.x = drawing_data->start.x;
	while (plot_pos.y <= drawing_data->end.y)
	{
		plot_index = (plot_pos.y * drawing_data->size_line) + plot_pos.x;
		if (img_buffer[plot_index] < drawing_data->color)
		{
			if ((plot_pos.y / 2) % 2 || drawing_data->line_type == 0)
				img_buffer[plot_index] = drawing_data->color;
			else
				img_buffer[plot_index] = 0;
		}
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

static void		initialize_drawing_data(t_drawing_data *drawing_data,
												t_img *img, t_elem_line *line)
{
	drawing_data->color = line->color;
	drawing_data->line_type = line->line_type;
	drawing_data->size_line = img->size_line / 4;
	return ;
}

static void		add_offset(t_drawing_data *drawing_data,
											t_position *elem_position_offset)
{
	drawing_data->start.x += elem_position_offset->x;
	drawing_data->start.y += elem_position_offset->y;
	drawing_data->end.x += elem_position_offset->x;
	drawing_data->end.y += elem_position_offset->y;
	return ;
}

void			bresenham_draw_line(t_img *img, t_elem_line *line,
											t_position *elem_position_offset)
{
	int				delta_x;
	int				delta_y;
	t_drawing_data	drawing_data;

	initialize_drawing_data(&drawing_data, img, line);
	delta_x = ft_abs(line->end->x - line->start->x);
	delta_y = ft_abs(line->end->y - line->start->y);
	if ((delta_y < delta_x && line->start->x > line->end->x) ||
		(delta_y > delta_x && line->start->y > line->end->y))
	{
		drawing_data.start = *line->end;
		drawing_data.end = *line->start;
	}
	else
	{
		drawing_data.start = *line->start;
		drawing_data.end = *line->end;
	}
	add_offset(&drawing_data, elem_position_offset);
	if (delta_y < delta_x)
		draw_low((unsigned int *)img->data, &drawing_data);
	else
		draw_high((unsigned int *)img->data, &drawing_data);
	return ;
}
