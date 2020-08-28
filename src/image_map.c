/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 11:28:10 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/28 13:45:21 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		add_line_to_image(t_mlx_image_data *img_data, t_point *point_array,
												int line_cnt, int array_size)
{
	int			factor;
	t_line		line;

	factor = 30;
	while (array_size--)
	{
		if (point_array[array_size].altitude)
			line.color = 0xff00ff;
		else
			line.color = 0xffffff;
		line.start_pos.x = array_size * factor;
		line.start_pos.y = line_cnt * factor;
		if (array_size)
		{
			line.end_pos.x = (array_size - 1) * factor;
			line.end_pos.y = line_cnt * factor;
			img_data->line = line;
			bresenham_draw_line(img_data, line);
		}
		if (line_cnt)
		{
			line.end_pos.x = array_size * factor;
			line.end_pos.y = (line_cnt - 1) * factor;
			img_data->line = line;
			bresenham_draw_line(img_data, line);
		}
	}
	return ;
}

void		add_tile_to_image(t_mlx_image_data *img_data, t_point *point_array,
												int line_cnt, int array_size)
{
	int				tile_size;
	t_vec2			cur_pos;
	int				plot_index;
	t_drawing_data	drawing_data;
	t_vec2			pixel_cnt;

	drawing_data.ints_in_image_line = img_data->line_bytes / 4;
	tile_size = 30;
	while (array_size--)
	{
		if (point_array[array_size].altitude)
			drawing_data.color = 0xff00ff;
		else
			drawing_data.color = 0x000000;
		cur_pos.y = line_cnt * tile_size;
		cur_pos.x = array_size * tile_size;
		pixel_cnt.y = tile_size;
		while (pixel_cnt.y--)
		{
			pixel_cnt.x = tile_size;
			while (pixel_cnt.x--)
			{
				plot_index = (cur_pos.y + pixel_cnt.y) * drawing_data.ints_in_image_line + cur_pos.x + pixel_cnt.x;
				img_data->img_buffer[plot_index] = drawing_data.color;
			}
		}
	}
	return ;
}
