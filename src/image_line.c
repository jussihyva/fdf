/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 14:34:08 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/27 10:58:25 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			initialize_line(t_line *line, int x, int y)
{
	line->color = 0 << 16;
	line->color += 250 << 8;
	line->color += 0;
	line->start_pos.x = 300;
	line->start_pos.y = 300;
	line->start_pos.z = 0;
	line->end_pos.x = x;
	line->end_pos.y = y;
	line->end_pos.z = 0;
	return ;
}

void				update_line_image(t_mlx_image_data *line_img_data,
												void *mlx_ptr, void *win_ptr)
{
	ft_bzero(line_img_data->img_buffer, line_img_data->img_buffer_size);
	bresenham_draw_line(line_img_data);
	mlx_put_image_to_window(mlx_ptr, win_ptr, line_img_data->img_ptr, 0, 0);
	return ;
}

t_mlx_image_data	*create_line_image(int width, int hight, void *mlx_ptr)
{
	t_mlx_image_data	*img_data;

	img_data = create_empty_image(width, hight, mlx_ptr);
	initialize_line(&img_data->line, width, hight);
	return (img_data);
}
