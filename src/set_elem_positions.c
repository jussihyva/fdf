/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elem_positions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 05:17:52 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/17 12:03:11 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			set_position(t_xyz_values *position, double x, double y,
																	double z)
{
	position->x = x;
	position->y = y;
	position->z = z;
}

t_xyz_values	*set_elem_positions(t_xyz_values *elem_size)
{
	t_xyz_values	*elem_positions;

	elem_positions = (t_xyz_values *)ft_memalloc(sizeof(*elem_positions) *
														NUM_OF_ELEM_POSITIONS);
	set_position(&elem_positions[0], 0, 0, 0);
	set_position(&elem_positions[1], elem_size->x, 0, 0);
	set_position(&elem_positions[2], 0, elem_size->y, 0);
	set_position(&elem_positions[3], elem_size->x, elem_size->y, 0);
	set_position(&elem_positions[4], 0, 0, elem_size->z);
	set_position(&elem_positions[5], elem_size->x, 0, elem_size->z);
	set_position(&elem_positions[6], 0, elem_size->y, elem_size->z);
	set_position(&elem_positions[7], elem_size->x, elem_size->y, elem_size->z);
	return (elem_positions);
}
