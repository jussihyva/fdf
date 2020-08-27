/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 10:57:33 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/27 10:58:33 by jkauppi          ###   ########.fr       */
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

t_mlx_image_data	*create_empty_image(int width, int hight, void *mlx_ptr)
{
	t_mlx_image_data	*img_data;

	img_data = (t_mlx_image_data *)ft_memalloc(sizeof(*img_data));
	img_data->width = width;
	img_data->hight = hight;
	img_data->img_ptr = mlx_new_image(mlx_ptr, width, hight);
	validate_mlx_parameters(img_data);
	return (img_data);
}
