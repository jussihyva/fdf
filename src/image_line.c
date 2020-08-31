/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 14:34:08 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/31 16:35:10 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			initialize_line(t_line *line, t_window window)
{
	line->color = 0 << 16;
	line->color += 250 << 8;
	line->color += 0;
	line->start_pos.x = 300;
	line->start_pos.y = 300;
	line->end_pos.x = window.width;
	line->end_pos.y = window.hight;
	return ;
}

void				update_line_image(t_mlx_img_data *line_img_data,
												void *mlx_ptr, void *win_ptr)
{
	ft_bzero(line_img_data->img_buffer, line_img_data->img_buffer_size);
	bresenham_draw_line(line_img_data->img_buffer, line_img_data->line,
												line_img_data->line_bytes / 4);
	mlx_put_image_to_window(mlx_ptr, win_ptr, line_img_data->img_ptr, 0, 0);
	return ;
}

t_mlx_img_data		*create_line_image(t_window window, void *mlx_ptr)
{
	t_mlx_img_data	*img_data;

	img_data = create_empty_image(window, mlx_ptr);
	initialize_line(&img_data->line, window);
	return (img_data);
}
