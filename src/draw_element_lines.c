/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_element_lines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 23:12:39 by juhani            #+#    #+#             */
/*   Updated: 2021/03/20 11:38:29 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			draw_lines(t_img *img, t_element *element)
{
	t_elem_line 	*elem_lines;
	t_elem_line 	elem_line;
	int				i;

	elem_lines = element->elem_lines;
	i = -1;
	ft_log_trace("Draw element lines %s %3.2f,%3.2f %s %3d,%3d",
			"(start position):", "(offset):",
			element->start_position->x, element->start_position->y,
			element->elem_position_offset.x, element->elem_position_offset.y);
	while (++i < 12)
	{
		elem_line = elem_lines[i];
		elem_line.color = element->color;
		bresenham_draw_line(img, &elem_line, &element->elem_position_offset);
	}
	return ;
}
