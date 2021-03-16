/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:26:13 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/16 22:45:03 by jkauppi          ###   ########.fr       */
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

static t_object_type	*create_new_object_type(double altitude,
		t_position *angle, t_xy_values object_xy_size, t_list **object_type_lst)
{
	t_list			*object_elem;
	t_object_type	*object_type;

	object_type = (t_object_type *)ft_memalloc(sizeof(*object_type));
	set_xyz_values(&object_type->angle, (double)angle->x,
											(double)angle->y, (double)angle->z);
	set_xyz_values(&object_type->size, object_xy_size.x,
													object_xy_size.y, altitude);
	object_type->start_positions = set_object_positions(&object_type->size);
	object_elem = ft_lstnew(&object_type, sizeof(object_type));
	ft_lstadd(object_type_lst, object_elem);
	return (object_type);
}

static t_object_type	*is_object_type_added(t_list **object_type_lst,
																double altitude)
{
	t_list			*object_elem;
	t_object_type	*object_type;

	object_elem = *object_type_lst;
	while (object_elem)
	{
		object_type = *(t_object_type **)object_elem->content;
		if (object_type->size.z == altitude)
			break ;
		object_elem = object_elem->next;
	}
	if (!object_elem)
		object_type = NULL;
	return (object_type);
}

void					create_object_types(t_list **object_type_lst,
					t_map *map, t_position *angle, t_xy_values object_xy_size)
{
	t_xy_values_int		index;
	size_t				obj_counter;
	double				altitude;

	obj_counter = 0;
	index.x = -1;
	while (++index.x < map->map_size->y)
	{
		index.y = -1;
		while (++index.y < map->map_size->x)
		{
			altitude = (double)map->elem_altitude[index.x][index.y];
			if (!(map->object_type = is_object_type_added(object_type_lst,
																	altitude)))
			{
				map->object_type = create_new_object_type(altitude, angle,
											object_xy_size, object_type_lst);
				obj_counter++;
			}
		}
	}
	ft_log_info("Number of object types: %u", obj_counter);
	return ;
}
