/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_element_lines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 23:12:39 by juhani            #+#    #+#             */
/*   Updated: 2021/03/11 13:15:26 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			draw_lines(t_img *img, t_element *element)
{
	t_elem_line 	*elem_lines;
	int				i;

	elem_lines = element->elem_lines;
	i = -1;
	while (++i < 12)
	{
		if (i == 1 || i == 5 || i == 6)
			elem_lines[i].line_type = 1;
		if (element->elem_size.z)
			elem_lines[i].color = 0x00FF0000;
		else
			elem_lines[i].color = 0x000000FF;
		bresenham_draw_line(img, &elem_lines[i], &element->elem_position_offset);
	}
	return ;
}
