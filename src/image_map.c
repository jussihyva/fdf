/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 11:28:10 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/31 19:27:33 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			add_line_to_image(t_input *input, t_mlx_img_data *img_data,
					int line_cnt, t_drawing_data drawing_data)
{
	int			tile_cnt;

	tile_cnt = -1;
	while (++tile_cnt < input->map_size.x)
	{
		img_data->line.color = (input->point_map[line_cnt][tile_cnt].altitude) ?
															0xff00ff : 0xffffff;
		img_data->line.start_pos.x = tile_cnt * drawing_data.tile_size;
		img_data->line.start_pos.y = line_cnt * drawing_data.tile_size;
		if (tile_cnt)
		{
			img_data->line.end_pos.x = (tile_cnt - 1) * drawing_data.tile_size;
			img_data->line.end_pos.y = line_cnt * drawing_data.tile_size;
			bresenham_draw_line(img_data->img_buffer, img_data->line,
													img_data->line_bytes / 4);
		}
		if (line_cnt)
		{
			img_data->line.end_pos.x = tile_cnt * drawing_data.tile_size;
			img_data->line.end_pos.y = (line_cnt - 1) * drawing_data.tile_size;
			bresenham_draw_line(img_data->img_buffer, img_data->line,
													img_data->line_bytes / 4);
		}
	}
	return ;
}

static void		set_tile_to_image(t_mlx_img_data *img_data, t_tile tile,
													t_drawing_data drawing_data)
{
	t_vec2		pixel_cnt;
	t_line		*line;
	double		angle_radian;
	int			ints_in_image_line;

	angle_radian = drawing_data.angle_radian;
	ints_in_image_line = drawing_data.ints_in_image_line;
	pixel_cnt.y = tile.size;
	line = &img_data->line;
	line->color = tile.color;
	while (pixel_cnt.y--)
	{
		line->start_pos.x = tile.pos.x * cos(angle_radian) - (tile.pos.y +
					pixel_cnt.y) * sin(angle_radian) + drawing_data.offset.x;
		line->start_pos.y = tile.pos.x * sin(angle_radian) + (tile.pos.y +
					pixel_cnt.y) * cos(angle_radian) + drawing_data.offset.y;
		line->end_pos.x = (tile.pos.x + tile.size) * cos(angle_radian) -
		(tile.pos.y + pixel_cnt.y) * sin(angle_radian) + drawing_data.offset.x;
		line->end_pos.y = (tile.pos.x + tile.size) * sin(angle_radian) +
		(tile.pos.y + pixel_cnt.y) * cos(angle_radian) + drawing_data.offset.y;
		bresenham_draw_line(img_data->img_buffer, img_data->line,
															ints_in_image_line);
	}
	return ;
}

void			add_tile_to_image(t_input *input, t_mlx_img_data *img_data,
									t_drawing_data drawing_data, int line_cnt)
{
	t_tile			tile;
	int				tile_cnt;

	tile.size = drawing_data.tile_size;
	tile.pos.y = line_cnt * drawing_data.tile_size;
	tile_cnt = -1;
	while (++tile_cnt < input->map_size.x)
	{
		if (input->point_map[line_cnt][tile_cnt].altitude)
			tile.color = 0xff00ff;
		else
			tile.color = 0x000000;
		tile.pos.x = tile_cnt * drawing_data.tile_size;
		set_tile_to_image(img_data, tile, drawing_data);
	}
	return ;
}
