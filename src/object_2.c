/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:59:49 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/22 17:01:46 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			set_xyz_values(t_xyz_values *position, double x,
															double y, double z)
{
	position->x = x;
	position->y = y;
	position->z = z;
}

t_xyz_values	*set_object_positions(t_xyz_values *object_size)
{
	t_xyz_values	*object_positions;

	ft_log_debug("Object size: x=%.0f y=%.0f z=%.0f", object_size->x,
												object_size->y, object_size->z);
	object_positions = (t_xyz_values *)ft_memalloc(sizeof(*object_positions) *
													NUM_OF_OBJECT_POSITIONS);
	set_xyz_values(&object_positions[0], 0, 0, 0);
	set_xyz_values(&object_positions[1], object_size->x, 0, 0);
	set_xyz_values(&object_positions[2], 0, object_size->y, 0);
	set_xyz_values(&object_positions[3], object_size->x, object_size->y, 0);
	set_xyz_values(&object_positions[4], 0, 0, object_size->z);
	set_xyz_values(&object_positions[5], object_size->x, 0, object_size->z);
	set_xyz_values(&object_positions[6], 0, object_size->y, object_size->z);
	set_xyz_values(&object_positions[7], object_size->x, object_size->y,
																object_size->z);
	return (object_positions);
}
