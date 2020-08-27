/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 11:28:10 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/27 13:59:16 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		add_point_to_image(t_mlx_image_data *img_data, t_point *point_array,
												int line_cnt, int array_size)
{
	int			int_lines;
	int			factor;
	t_point		point;
	int			dots;

	factor = 30;
	int_lines = img_data->line_bytes / 4;
	while (array_size--)
	{
		point = point_array[array_size];
		dots = 7;
		while (dots--)
		{
			img_data->img_buffer[(factor * (line_cnt + dots) * int_lines) +
										array_size * factor] = point.color;
			img_data->img_buffer[(factor * (line_cnt + dots) * int_lines) +
										array_size * factor + 1] = point.color;
			img_data->img_buffer[(factor * (line_cnt + dots) * int_lines) +
										array_size * factor + 2] = point.color;
			img_data->img_buffer[(factor * (line_cnt + dots) * int_lines) +
										array_size * factor + 3] = point.color;
			img_data->img_buffer[(factor * (line_cnt + dots) * int_lines) +
										array_size * factor + 4] = point.color;
			img_data->img_buffer[(factor * (line_cnt + dots) * int_lines) +
										array_size * factor + 5] = point.color;
			img_data->img_buffer[(factor * (line_cnt + dots) * int_lines) +
										array_size * factor + 6] = point.color;
		}
	}
	return ;
}
