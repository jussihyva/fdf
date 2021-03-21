/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_line_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 08:27:27 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/21 08:34:46 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_drawing_data_1(t_drawing_data *drawing_data, t_elem_line *line)
{
	drawing_data->start.x = (int)line->start->x +
									line->start_elem->elem_position_offset.x;
	drawing_data->start.y = (int)line->start->y +
									line->start_elem->elem_position_offset.y;
	drawing_data->end.x = (int)line->end->x +
									line->end_elem->elem_position_offset.x;
	drawing_data->end.y = (int)line->end->y +
									line->end_elem->elem_position_offset.y;
	return ;
}

static void	set_drawing_data_2(t_drawing_data *drawing_data, t_elem_line *line)
{
	drawing_data->end.x = (int)line->start->x +
									line->start_elem->elem_position_offset.x;
	drawing_data->end.y = (int)line->start->y +
									line->start_elem->elem_position_offset.y;
	drawing_data->start.x = (int)line->end->x +
									line->end_elem->elem_position_offset.x;
	drawing_data->start.y = (int)line->end->y +
									line->end_elem->elem_position_offset.y;
	return ;
}

int		set_drawing_data(t_drawing_data *drawing_data,
											t_elem_line *line, t_delta *delta)
{
	int			low;

	if ((delta->x >= delta->y && line->start->x > line->end->x) ||
		(delta->y >= delta->x && line->start->y > line->end->y))
		set_drawing_data_2(drawing_data, line);
	else
		set_drawing_data_1(drawing_data, line);
	low = (drawing_data->start.x < drawing_data->end.x) ? 1 : 0;
	return (low);
}
