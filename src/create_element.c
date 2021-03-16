/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_element.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 03:44:46 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/17 00:12:26 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			set_elem_line(t_elem_line *elem_line, t_position *start,
																t_position *end)
{
	elem_line->start = start;
	elem_line->end = end;
	elem_line->line_type = 0;
	return ;
}

static t_elem_line	*set_elem_lines(t_position *elem_positions)
{
	t_elem_line		*elem_lines;
	int				num_of_lines;

	num_of_lines = 12;
	elem_lines = (t_elem_line *)ft_memalloc(sizeof(*elem_lines) *
																num_of_lines);
	set_elem_line(&elem_lines[0], &elem_positions[0], &elem_positions[1]);
	set_elem_line(&elem_lines[1], &elem_positions[0], &elem_positions[2]);
	set_elem_line(&elem_lines[2], &elem_positions[0], &elem_positions[4]);
	set_elem_line(&elem_lines[3], &elem_positions[1], &elem_positions[3]);
	set_elem_line(&elem_lines[4], &elem_positions[1], &elem_positions[5]);
	set_elem_line(&elem_lines[5], &elem_positions[2], &elem_positions[3]);
	set_elem_line(&elem_lines[6], &elem_positions[2], &elem_positions[6]);
	set_elem_line(&elem_lines[7], &elem_positions[3], &elem_positions[7]);
	set_elem_line(&elem_lines[8], &elem_positions[4], &elem_positions[5]);
	set_elem_line(&elem_lines[9], &elem_positions[4], &elem_positions[6]);
	set_elem_line(&elem_lines[10], &elem_positions[5], &elem_positions[7]);
	set_elem_line(&elem_lines[11], &elem_positions[6], &elem_positions[7]);
	return (elem_lines);
}

t_element			*create_element(t_mlx_win *mlx_win,
						t_position *start_position, t_position *position_offset,
						t_object_type *object_type)
{
	t_element	*element;

	element = (t_element *)ft_memalloc(sizeof(*element));
	element->angle = (t_position *)ft_memalloc(sizeof(*element->angle));
	element->object_type = object_type;
	element->start_position =
					(t_position *)ft_memalloc(sizeof(*element->start_position));
	ft_memcpy(element->angle, mlx_win->angle, sizeof(*mlx_win->angle));
	element->current_positions =
			(t_position *)ft_memalloc(sizeof(*element->current_positions) *
														NUM_OF_ELEM_POSITIONS);
	element->start_positions = set_elem_positions(&object_type->size);
	elemental_rotation(element, element->angle, position_offset,
																start_position);
	element->elem_lines = set_elem_lines(element->current_positions);
	ft_memcpy(element->start_position, start_position,
											sizeof(*element->start_position));
	return (element);
}
