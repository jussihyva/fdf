/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 14:34:08 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/23 17:24:21 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		fatal_error(void)
{
	ft_printf("Fatal error: Unexpected rseult from the");
	ft_printf(" validation of mlx parammeters function!\n");
	exit(0);
}

static char		*validate_mlx_parameters(void *image_line, int *line_bytes,
																int image_width)
{
	char		*char_buffer;
	int			pixel_bits;
	int			endian;

	char_buffer = mlx_get_data_addr(image_line, &pixel_bits, line_bytes,
																	&endian);
	if (!(pixel_bits == 32 && endian == 0 && *line_bytes == 4 * image_width))
	{
		ft_printf("image_line: %d, line_bytes: %d, endian: %d\n", pixel_bits,
														*line_bytes, endian);
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
	line->start_pos.x = 0;
	line->start_pos.y = 0;
	line->start_pos.z = 0;
	line->end_pos.x = x;
	line->end_pos.y = y;
	line->end_pos.z = 0;
	return ;
}

static void		draw_line(void *line_img, int x, int y)
{
	char			*char_buffer;
	int				*int_buffer;
	int				line_bytes;
	t_line			line;

	initialize_line(&line, x, y);
	char_buffer = validate_mlx_parameters(line_img, &line_bytes,
										line.end_pos.x - line.start_pos.x + 1);
	int_buffer = (int *)char_buffer;
	line.current_pos.x = line.start_pos.x;
	line.current_pos.y = line.start_pos.y;
	line.current_pos.z = line.start_pos.z;
	bresenham_draw_line_1(int_buffer, &line, line_bytes / 4);
	return ;
}

void			*create_line_image(t_fdf_data *fdf_data, int x, int y)
{
	void			*line_img;

	line_img = mlx_new_image(fdf_data->mlx_ptr, x + 1, y + 1);
	draw_line(line_img, x, y);
	return (line_img);
}
