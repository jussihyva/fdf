/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 11:28:10 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/27 14:39:48 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		add_point_to_image(t_mlx_image_data *img_data, t_point *point_array,
												int line_cnt, int array_size)
{
	int			int_lines;
	int			factor;
	t_line 		line;

	factor = 30;
	int_lines = img_data->line_bytes / 4;
	while (array_size--)
	{
		if (array_size)
		{
			line.color = point_array[array_size].color;
			line.start_pos.x = array_size * factor;
			line.start_pos.y = line_cnt * factor;
			line.end_pos.x = (array_size - 1) * factor;
			line.end_pos.y = line_cnt * factor;
			img_data->line = line;
			bresenham_draw_line(img_data, line);
		}
		if (line_cnt)
		{
			line.color = point_array[array_size].color;
			line.start_pos.x = array_size * factor;
			line.start_pos.y = line_cnt * factor;
			line.end_pos.x = array_size * factor;
			line.end_pos.y = (line_cnt - 1) * factor;
			img_data->line = line;
			bresenham_draw_line(img_data, line);
		}
	}
	return ;
}
