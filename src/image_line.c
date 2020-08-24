/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 14:34:08 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/24 21:33:12 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		fatal_error(void)
{
	ft_printf("Fatal error: Unexpected rseult from the");
	ft_printf(" validation of mlx parammeters function!\n");
	exit(0);
}

char			*validate_mlx_parameters(void *image_line, int *line_bytes,
																int image_width)
{
	char		*char_buffer;
	int			pixel_bits;
	int			endian;

	char_buffer = mlx_get_data_addr(image_line, &pixel_bits, line_bytes,
																	&endian);
	if (!(pixel_bits == 32 && endian == 0 && *line_bytes == 4 * image_width))
	{
		ft_printf("image_line: %d, line_bytes: %d(%d), endian: %d\n",
							pixel_bits, *line_bytes, 4 * image_width , endian);
		char_buffer = NULL;
		fatal_error();
	}
	return (char_buffer);
}

static void		initialize_line(t_line *line, int x, int y)
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

void			create_line_image(t_fdf_data *fdf_data, int x, int y)
{
	fdf_data->line_img = mlx_new_image(fdf_data->mlx_ptr,
								fdf_data->window.width, fdf_data->window.hight);
	initialize_line(&fdf_data->line, x, y);
	bresenham_draw_line(fdf_data);
	mlx_put_image_to_window(fdf_data->mlx_ptr, fdf_data->win_ptr,
													fdf_data->line_img, 0, 0);
	return ;
}
