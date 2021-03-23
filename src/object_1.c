/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:26:13 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/23 23:43:01 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
			altitude = (double)map->elem_altitude[i][j] * map->alt_factor;
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
