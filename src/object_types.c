/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:26:13 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/12 16:46:32 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void				set_xyz_values(t_xyz_values *position, double x,
															double y, double z)
{
	position->x = x;
	position->y = y;
	position->z = z;
}

static t_xyz_values		*set_object_positions(t_xyz_values *object_size)
{
	t_xyz_values	*object_pos;

	object_pos = (t_xyz_values *)ft_memalloc(sizeof(*object_pos) *
													NUM_OF_OBJECT_POSITIONS);
	set_xyz_values(&object_pos[0], 0, 0, 0);
	set_xyz_values(&object_pos[1], object_size->x, 0, 0);
	set_xyz_values(&object_pos[3], object_size->x, object_size->y, 0);
	set_xyz_values(&object_pos[2], 0, object_size->y, 0);
	set_xyz_values(&object_pos[4], 0, 0, object_size->z);
	set_xyz_values(&object_pos[5], object_size->x, 0, object_size->z);
	set_xyz_values(&object_pos[6], 0, object_size->y, object_size->z);
	set_xyz_values(&object_pos[7], object_size->x, object_size->y,
																object_size->z);
	return (object_pos);
}

t_list					**create_object_types(t_map *map, t_position *angle,
													t_xy_values object_xy_size)
{
	t_list			**object_type_lst;
	t_list			*object_elem;
	t_object_type	*object_type;
	t_xyz_values	object_size;
	int				i;
	int				j;

	object_type_lst = (t_list **)ft_memalloc(sizeof(*object_type_lst));
	i = -1;
	while (++i < map->map_size->y)
	{
		j = -1;
		while (++j < map->map_size->x)
		{
			object_type = (t_object_type *)ft_memalloc(sizeof(*object_type));
			object_type->angle.x = (double)angle->x;
			object_type->angle.y = (double)angle->y;
			object_type->angle.z = (double)angle->z;
			set_xyz_values(&object_size, object_xy_size.x, object_xy_size.y,
											(double)map->elem_altitude[i][j]);
			ft_log_debug("Object size: x=%.0f y=%.0f z=%.0f", object_size.x,
												object_size.y, object_size.z);
			object_type->start_positions = set_object_positions(&object_size);
			object_elem = ft_lstnew(&object_type, sizeof(object_type));
		}
	}
	return (object_type_lst);
}
