/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 10:57:33 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/27 13:33:52 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			fatal_error(void)
{
	ft_printf("Fatal error: Unexpected rseult from the");
	ft_printf(" validation of mlx parammeters function!\n");
	exit(0);
}

static void			validate_mlx_parameters(t_mlx_image_data *img_data)
{
	img_data->img_buffer = (int *)mlx_get_data_addr(img_data->img_ptr,
						&img_data->pixel_bits, &img_data->line_bytes,
														&img_data->endian);
	if (!(img_data->pixel_bits == 32 && img_data->endian == 0 &&
						img_data->line_bytes == img_data->width *
												img_data->pixel_bits / 8))
	{
		ft_printf("image_line: %d, line_bytes: %d(%d), endian: %d\n",
						img_data->pixel_bits, img_data->line_bytes,
							4 * img_data->width, img_data->endian);
		fatal_error();
	}
	img_data->img_buffer_size = img_data->hight *
						img_data->width * img_data->pixel_bits / 8;
	ft_bzero(img_data->img_buffer, img_data->img_buffer_size);
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
