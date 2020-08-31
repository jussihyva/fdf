/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 10:57:33 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/31 18:45:24 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// static int			ft_min(int i1, int i2)
// {
// 	if (i1 < i2)
// 		return (i1);
// 	else
// 		return (i2);
// }

static int			ft_max(int i1, int i2)
{
	if (i1 > i2)
		return (i1);
	else
		return (i2);
}

static void			fatal_error(void)
{
	ft_printf("Fatal error: Unexpected rseult from the");
	ft_printf(" validation of mlx parammeters function!\n");
	exit(0);
}

static t_vec2		count_offest(t_drawing_data drawing_data, t_vec2 map_size)
{
	t_vec2		offset;
	double		cos_angle_radian;
	double		sin_angle_radian;
	int			tile_size;

	cos_angle_radian = cos(drawing_data.angle_radian);
	sin_angle_radian = sin(drawing_data.angle_radian);
	tile_size = drawing_data.tile_size;
	offset.x = ft_max(0, -(0 * cos_angle_radian - (tile_size * map_size.y) *
															sin_angle_radian));
	offset.x = ft_max(offset.x, -((tile_size * map_size.x) * cos_angle_radian -
								(tile_size * map_size.y) * sin_angle_radian));
	offset.x = ft_max(offset.x, -((tile_size * map_size.x) * cos_angle_radian -
										(tile_size * 0) * sin_angle_radian));
	offset.y = ft_max(0, -(0 * sin_angle_radian + (tile_size * map_size.y) *
															cos_angle_radian));
	offset.y = ft_max(offset.y, -((tile_size * map_size.x) * sin_angle_radian +
								(tile_size * map_size.y) * cos_angle_radian));
	offset.y = ft_max(offset.y, -((tile_size * map_size.x) * sin_angle_radian +
								(tile_size * 0) * cos_angle_radian));
	return (offset);
}

static void			validate_mlx_parameters(t_mlx_img_data *img_data)
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

t_mlx_img_data		*create_empty_image(t_window window, void *mlx_ptr)
{
	t_mlx_img_data	*img_data;

	img_data = (t_mlx_img_data *)ft_memalloc(sizeof(*img_data));
	img_data->width = window.width;
	img_data->hight = window.hight;
	img_data->img_ptr = mlx_new_image(mlx_ptr, window.width, window.hight);
	validate_mlx_parameters(img_data);
	return (img_data);
}

void				create_picture(t_input *input, t_mlx_img_data *img_data)
{
	int				line_cnt;
	t_drawing_data	drawing_data;

	drawing_data.tile_size = 30;
	drawing_data.angle_radian = input->angle * PI / 180;
	drawing_data.ints_in_image_line = img_data->line_bytes / 4;
	drawing_data.offset = count_offest(drawing_data, input->map_size);
	line_cnt = -1;
	while (++line_cnt < input->map_size.y)
	{
		if (input->projection_plane == e_orthographic_top_view_line)
			add_line_to_image(input, img_data, line_cnt, drawing_data);
		else
			add_tile_to_image(input, img_data, drawing_data, line_cnt);
	}
	return ;
}
