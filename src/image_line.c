/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 14:34:08 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/25 13:35:55 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			fatal_error(void)
{
	ft_printf("Fatal error: Unexpected rseult from the");
	ft_printf(" validation of mlx parammeters function!\n");
	exit(0);
}

static void			validate_mlx_parameters(t_mlx_image_data *line_img_data)
{
	line_img_data->img_buffer = (int *)mlx_get_data_addr(line_img_data->img_ptr,
						&line_img_data->pixel_bits, &line_img_data->line_bytes,
														&line_img_data->endian);
	if (!(line_img_data->pixel_bits == 32 && line_img_data->endian == 0 &&
						line_img_data->line_bytes == line_img_data->width *
												line_img_data->pixel_bits / 8))
	{
		ft_printf("image_line: %d, line_bytes: %d(%d), endian: %d\n",
						line_img_data->pixel_bits, line_img_data->line_bytes,
							4 * line_img_data->width, line_img_data->endian);
		fatal_error();
	}
	line_img_data->img_buffer_size = line_img_data->hight *
						line_img_data->width * line_img_data->pixel_bits / 8;
	return ;
}

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

void				update_line_image(t_mlx_image_data *line_img_data, void *mlx_ptr, void *win_ptr)
{
	ft_bzero(line_img_data->img_buffer, line_img_data->img_buffer_size);
	bresenham_draw_line(line_img_data);
	mlx_put_image_to_window(mlx_ptr, win_ptr, line_img_data->img_ptr, 0, 0);
	return ;
}

t_mlx_image_data	*create_line_image(int width, int hight, void *mlx_ptr)
{
	t_mlx_image_data	*img_data;

	img_data = (t_mlx_image_data *)ft_memalloc(sizeof(*img_data));
	img_data->width = width;
	img_data->hight = hight;
	img_data->img_ptr = mlx_new_image(mlx_ptr, width, hight);
	validate_mlx_parameters(img_data);
	initialize_line(&img_data->line, width, hight);
	return (img_data);
}
