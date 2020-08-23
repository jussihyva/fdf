/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 16:19:56 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/23 17:05:53 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		bresenham_draw_line_1(int *buffer, t_line *line, int line_length)
{
	int		delta_x;
	int		delta_y;
	int		difference;
	int		x;
	int		y;

	delta_x = line->end_pos.x - line->start_pos.x;
	delta_y = line->end_pos.y - line->start_pos.y;
	difference = 2 * delta_y - delta_x;
	ft_printf("dx:%d dy:%d diff:%d\n", delta_x, delta_y, difference);
	y = line->start_pos.y;
	x = line->start_pos.x;
	while (x <= line->end_pos.x)
	{
		buffer[(y * line_length) + x] = line->color;
		if (difference > 0)
		{
			y++;
			difference -= (2 * delta_x);
		}
		difference += (2 * delta_y);
		x++;
	}
	return ;
}
