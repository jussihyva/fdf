/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_line_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 08:27:27 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/22 09:23:21 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		swap_start_and_end(t_drawing_data *drawing_data)
{
	t_xy_values_int		tmp;

	ft_memcpy(&tmp, &drawing_data->end, sizeof(tmp));
	ft_memcpy(&drawing_data->end, &drawing_data->start, sizeof(tmp));
	ft_memcpy(&drawing_data->start, &tmp, sizeof(tmp));
	return ;
}

int				set_drawing_data(t_drawing_data *drawing_data, t_delta *delta)
{
	int			low;

	delta->x = ft_abs(drawing_data->end.x - drawing_data->start.x);
	delta->y = ft_abs(drawing_data->end.y - drawing_data->start.y);
	if ((delta->x >= delta->y && drawing_data->start.x > drawing_data->end.x) ||
		(delta->y >= delta->x && drawing_data->start.y > drawing_data->end.y))
		swap_start_and_end(drawing_data);
	low = (drawing_data->start.x < drawing_data->end.x) ? 1 : 0;
	return (low);
}
