/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_image_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:46:18 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/22 15:47:02 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		add_image_line(t_list **img_line_lst,
							t_element *start_element, t_element *end_element)
{
	t_elem_line		*elem_line;
	t_list			*elem;

	elem_line = (t_elem_line *)ft_memalloc(sizeof(*elem_line));
	elem_line->start = &start_element->object_type->current_positions[4];
	elem_line->start_elem = start_element;
	elem_line->end = &end_element->object_type->current_positions[4];
	elem_line->end_elem = end_element;
	elem_line->color = start_element->color;
	elem = ft_lstnew(&elem_line, sizeof(elem_line));
	ft_lstadd(img_line_lst, elem);
	return ;
}

void			add_image_lines(t_list **img_line_lst,
										t_element ***elem_table, int i, int j)
{
	if (i)
		add_image_line(img_line_lst, elem_table[i][j], elem_table[i - 1][j]);
	if (j)
		add_image_line(img_line_lst, elem_table[i][j], elem_table[i][j - 1]);
	return ;
}
