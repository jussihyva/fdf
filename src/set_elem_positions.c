/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elem_positions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 05:17:52 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/16 23:43:36 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			set_position(t_position *position, int x, int y, int z)
{
	position->x = x;
	position->y = y;
	position->z = z;
}

t_position		*set_elem_positions(t_xyz_values *elem_size)
{
	t_position		*elem_positions;

	elem_positions = (t_position *)ft_memalloc(sizeof(*elem_positions) *
														NUM_OF_ELEM_POSITIONS);
	set_position(&elem_positions[0], 0, 0, 0);
	set_position(&elem_positions[1], (int)elem_size->x, 0, 0);
	set_position(&elem_positions[2], 0, (int)elem_size->y, 0);
	set_position(&elem_positions[3], (int)elem_size->x, (int)elem_size->y, 0);
	set_position(&elem_positions[4], 0, 0, (int)elem_size->z);
	set_position(&elem_positions[5], (int)elem_size->x, 0, (int)elem_size->z);
	set_position(&elem_positions[6], 0, (int)elem_size->y, (int)elem_size->z);
	set_position(&elem_positions[7], (int)elem_size->x, (int)elem_size->y, (int)elem_size->z);
	return (elem_positions);
}
