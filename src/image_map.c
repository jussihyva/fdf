/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 11:28:10 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/31 12:46:35 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			add_line_to_image(t_mlx_image_data *img_data,
							t_point *point_array, int line_cnt, int array_size)
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
			bresenham_draw_line(img_data->img_buffer, line,
													img_data->line_bytes / 4);
		}
		if (line_cnt)
		{
			line.end_pos.x = array_size * factor;
			line.end_pos.y = (line_cnt - 1) * factor;
			img_data->line = line;
			bresenham_draw_line(img_data->img_buffer, line,
													img_data->line_bytes / 4);
		}
	}
	return ;
}

static void		set_tile_to_image(int *img_buffer, t_tile tile,
														int ints_in_image_line, int angle)
{
	t_vec2		pixel_cnt;
	t_line		line;

	pixel_cnt.y = tile.size;
	line.color = tile.color;
	while (pixel_cnt.y--)
	{
		line.start_pos.x = tile.pos.x * cos(angle) - (tile.pos.y + pixel_cnt.y) * sin(angle);
		line.start_pos.y = tile.pos.x * sin(angle) + (tile.pos.y + pixel_cnt.y) * cos(angle);
		line.end_pos.x = (tile.pos.x + tile.size) * cos(angle) - (tile.pos.y + pixel_cnt.y) * sin(angle);
		line.end_pos.y = (tile.pos.x + tile.size) * sin(angle) + (tile.pos.y + pixel_cnt.y) * cos(angle);
		// line.start_pos.x = tile.pos.x;
		// line.start_pos.y = tile.pos.y + pixel_cnt.y;
		// line.end_pos.x = tile.pos.x + tile.size;
		// line.end_pos.y = tile.pos.y + pixel_cnt.y;
		bresenham_draw_line(img_buffer, line, ints_in_image_line);
	}
	return ;
}

void			add_tile_to_image(t_mlx_image_data *img_data,
							t_point *point_array, int line_cnt, int array_size, int angle)
{
	int				tile_size;
	t_vec2			cur_pos;
	t_drawing_data	drawing_data;
	t_tile			tile;

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
		tile.color = drawing_data.color;
		tile.pos = cur_pos;
		tile.size = tile_size;
		set_tile_to_image(img_data->img_buffer, tile,
											drawing_data.ints_in_image_line, angle);
	}
	return ;
}
