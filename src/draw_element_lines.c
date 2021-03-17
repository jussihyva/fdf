/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_element_lines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 23:12:39 by juhani            #+#    #+#             */
/*   Updated: 2021/03/17 15:27:36 by jkauppi          ###   ########.fr       */
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
	while (++i < 12)
	{
		elem_line = elem_lines[i];
		if (i == 1 || i == 5 || i == 6)
			elem_line.line_type = 1;
		if (element->object_type->size.z)
			elem_line.color = 0x00FF0000;
		else
			elem_line.color = 0x000000FF;
		bresenham_draw_line(img, &elem_line, &element->elem_position_offset);
	}
	return ;
}
