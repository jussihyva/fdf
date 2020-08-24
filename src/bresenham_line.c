/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 16:19:56 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/24 13:01:52 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		draw_line_low(int *buffer, t_line *line, int line_length)
{
	int		delta_x;
	int		delta_y;
	int		difference;
	int		x;
	int		y;
	int		step;

	delta_x = ft_abs(line->end_pos.x - line->start_pos.x);
	delta_y = ft_abs(line->end_pos.y - line->start_pos.y);
	difference = 2 * delta_y - delta_x;
	if (line->end_pos.y < line->start_pos.y)
		step = -1;
	else
		step = 1;
	ft_printf("dx:%d dy:%d diff:%d step:%d\n", delta_x, delta_y, difference, step);
	y = line->start_pos.y;
	x = line->start_pos.x;
	while (x <= line->end_pos.x)
	{
		buffer[(y * line_length) + x] = line->color;
		ft_printf("    x:%d y:%d\n", x, y);
		if (difference > 0)
		{
			y += step;
			difference -= (2 * delta_x);
		}
		difference += (2 * delta_y);
		x++;
	}
	return ;
}

static void		draw_line_high(int *buffer, t_line *line, int line_length)
{
	int		delta_x;
	int		delta_y;
	int		difference;
	int		x;
	int		y;
	int		step;

	delta_x = ft_abs(line->end_pos.x - line->start_pos.x);
	delta_y = ft_abs(line->end_pos.y - line->start_pos.y);
	difference = 2 * delta_y - delta_x;
	if (line->end_pos.x < line->start_pos.x)
		step = -1;
	else
		step = 1;
	ft_printf("dx:%d dy:%d diff:%d step:%d\n", delta_x, delta_y, difference, step);
	y = line->start_pos.y;
	x = line->start_pos.x;
	while (y <= line->end_pos.y)
	{
		buffer[(y * line_length) + x] = line->color;
		ft_printf("    x:%d y:%d len:%d\n", x, y, line_length);
		if (difference > 0)
		{
			x += step;
			difference -= (2 * delta_y);
		}
		difference += (2 * delta_x);
		y++;
	}
	return ;
}

void		bresenham_draw_line_1(int *buffer, t_line *line, int line_length)
{
	int		delta_x;
	int		delta_y;
	t_vec3	tmp;

	delta_x = ft_abs(line->end_pos.x - line->start_pos.x);
	delta_y = ft_abs(line->end_pos.y - line->start_pos.y);
	if (delta_y < delta_x)
	{
		if (line->start_pos.x > line->end_pos.x)
		{
			ft_printf("Low neg\n");
			tmp = line->start_pos;
			line->start_pos = line->end_pos;
			line->end_pos = tmp;
		}
		else
			ft_printf("Low pos\n");
		draw_line_low(buffer, line, line_length);
	}
	else
	{
		if (line->start_pos.y > line->end_pos.y)
		{
			ft_printf("High neg\n");
			tmp = line->start_pos;
			line->start_pos = line->end_pos;
			line->end_pos = tmp;
		}
		else
			ft_printf("High pos\n");
		draw_line_high(buffer, line, line_length);
	}
	return ;
}
