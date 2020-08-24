/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 16:19:56 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/24 21:33:00 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		draw_line_low(t_fdf_data *fdf_data, int integers_in_line, t_vec3 start_pos, t_vec3 end_pos)
{
	int		delta_x;
	int		delta_y;
	int		difference;
	int		x;
	int		y;
	int		step;

	delta_x = ft_abs(end_pos.x - start_pos.x);
	delta_y = ft_abs(end_pos.y - start_pos.y);
	difference = 2 * delta_y - delta_x;
	if (end_pos.y < start_pos.y)
		step = -1;
	else
		step = 1;
	ft_printf("dx:%d dy:%d diff:%d step:%d\n", delta_x, delta_y, difference, step);
	y = start_pos.y;
	x = start_pos.x;
	while (x <= end_pos.x)
	{
		fdf_data->int_buffer[(y * integers_in_line) + x] = fdf_data->line.color;
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

static void		draw_line_high(t_fdf_data *fdf_data, int integers_in_line, t_vec3 start_pos, t_vec3 end_pos)
{
	int		delta_x;
	int		delta_y;
	int		difference;
	int		x;
	int		y;
	int		step;

	delta_x = ft_abs(end_pos.x - start_pos.x);
	delta_y = ft_abs(end_pos.y - start_pos.y);
	difference = 2 * delta_x - delta_y;
	if (end_pos.x < start_pos.x)
		step = -1;
	else
		step = 1;
	ft_printf("dx:%d dy:%d diff:%d step:%d\n", delta_x, delta_y, difference, step);
	y = start_pos.y;
	x = start_pos.x;
	while (y <= end_pos.y)
	{
		fdf_data->int_buffer[(y * integers_in_line) + x] = fdf_data->line.color;
		ft_printf("    x:%d y:%d\n", x, y);
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

void		bresenham_draw_line(t_fdf_data *fdf_data)
{
	int		delta_x;
	int		delta_y;
	int		line_bytes;

	fdf_data->int_buffer = (int *)validate_mlx_parameters(fdf_data->line_img, &line_bytes, fdf_data->window.width);
	delta_x = ft_abs(fdf_data->line.end_pos.x - fdf_data->line.start_pos.x);
	delta_y = ft_abs(fdf_data->line.end_pos.y - fdf_data->line.start_pos.y);
	if (delta_y < delta_x)
	{
		if (fdf_data->line.start_pos.x > fdf_data->line.end_pos.x)
		{
			ft_printf("Low neg\n");
			draw_line_low(fdf_data, line_bytes / 4, fdf_data->line.end_pos, fdf_data->line.start_pos);
		}
		else
		{
			ft_printf("Low pos\n");
			draw_line_low(fdf_data, line_bytes / 4, fdf_data->line.start_pos, fdf_data->line.end_pos);
		}
	}
	else
	{
		if (fdf_data->line.start_pos.y > fdf_data->line.end_pos.y)
		{
			ft_printf("High neg\n");
			draw_line_high(fdf_data, line_bytes / 4, fdf_data->line.end_pos, fdf_data->line.start_pos);
		}
		else
		{
			ft_printf("High pos\n");
			draw_line_high(fdf_data, line_bytes / 4, fdf_data->line.start_pos, fdf_data->line.end_pos);
		}
	}
	return ;
}
