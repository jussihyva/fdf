/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:26:13 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/17 14:17:28 by jkauppi          ###   ########.fr       */
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
									t_input *input, t_list **object_type_lst)
{
	t_list			*object_elem;
	t_object_type	*object_type;

	object_type = (t_object_type *)ft_memalloc(sizeof(*object_type));
	set_xyz_values(&object_type->angle, (double)input->angle->x,
							(double)input->angle->y, (double)input->angle->z);
	set_xyz_values(&object_type->size, input->object_xy_size.x,
											input->object_xy_size.y, altitude);
	object_type->start_positions = set_object_positions(&object_type->size);
	object_type->current_positions =
		(t_xyz_values *)ft_memalloc(sizeof(*object_type->current_positions) *
													NUM_OF_OBJECT_POSITIONS);
	ft_memcpy(object_type->current_positions, object_type->start_positions,
			sizeof(*object_type->current_positions) * NUM_OF_OBJECT_POSITIONS);
	object_elem = ft_lstnew(&object_type, sizeof(object_type));
	ft_lstadd(object_type_lst, object_elem);
	return (object_type);
}

static t_object_type	*get_object_type(t_list **object_type_lst,
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

static t_object_type	***initialize_objet_type(t_map *map)
{
	t_object_type		***object_type;
	int					i;

	object_type = (t_object_type ***)ft_memalloc(sizeof(*object_type) *
															map->map_size->y);
	i = -1;
	while (++i < map->map_size->y)
		object_type[i] = (t_object_type **)ft_memalloc(sizeof(*object_type[i]) *
															map->map_size->x);
	return (object_type);
}

void					create_object_types(t_list **object_type_lst,
													t_map *map, t_input *input)
{
	double				altitude;
	t_object_type		*object_type;
	int					i;
	int					j;

	map->object_type = initialize_objet_type(map);
	i = -1;
	while (++i < map->map_size->y)
	{
		j = -1;
		while (++j < map->map_size->x)
		{
			altitude = (double)map->elem_altitude[i][j] *
											input->cmd_args->altitude_factor;
			if (!(object_type = get_object_type(object_type_lst, altitude)))
			{
				object_type = create_new_object_type(altitude, input,
															object_type_lst);
				map->obj_counter++;
			}
			map->object_type[i][j] = object_type;
		}
	}
	ft_log_info("Number of object types: %u", map->obj_counter);
	return ;
}
