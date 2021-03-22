/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elemental_rotation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 20:46:08 by juhani            #+#    #+#             */
/*   Updated: 2021/03/22 16:29:24 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		rotate(t_xyz_values *position, t_xyz_values *angle)
{
	static size_t			vector_size = 3;
	static t_matrix_size	matrix_size = {3, 3};
	double					vector[vector_size];
	double					result_vector[vector_size];
	double					**rotation_matrix;

	vector[0] = position->x;
	vector[1] = position->y;
	vector[2] = position->z;
	rotation_matrix = get_z_rotation_matrix(angle->z);
	ft_matrix_x_vector_double(matrix_size, rotation_matrix, vector,
													result_vector);
	ft_memcpy(vector, result_vector, sizeof(vector));
	rotation_matrix = get_y_rotation_matrix(angle->y);
	ft_matrix_x_vector_double(matrix_size, rotation_matrix, vector,
													result_vector);
	ft_memcpy(vector, result_vector, sizeof(vector));
	rotation_matrix = get_x_rotation_matrix(angle->x);
	ft_matrix_x_vector_double(matrix_size, rotation_matrix, vector,
													result_vector);
	position->x = result_vector[0];
	position->y = result_vector[1];
	position->z = result_vector[2];
}

void		get_max_position_offset(t_xyz_values *current_positions,
					t_xyz_values *position_offset, t_xyz_values *start_position)
{
	size_t		i;

	i = -1;
	while (++i < NUM_OF_ELEM_POSITIONS)
	{
		position_offset->x = ft_max_double(position_offset->x,
													-(current_positions[i].x +
														start_position->x));
		position_offset->y = ft_max_double(position_offset->y,
													-(current_positions[i].y +
														start_position->y));
		position_offset->z = ft_max_double(position_offset->z,
													-(current_positions[i].z +
														start_position->z));
	}
	return ;
}

void		rotate_objects(t_list **object_type_lst, t_xyz_values *angle)
{
	t_list			*elem;
	t_object_type	*object_type;
	size_t			i;

	elem = *object_type_lst;
	while (elem)
	{
		object_type = *(t_object_type **)elem->content;
		ft_memcpy(&object_type->angle, angle, sizeof(object_type->angle));
		ft_memcpy(object_type->current_positions, object_type->start_positions,
			sizeof(*object_type->current_positions) * NUM_OF_OBJECT_POSITIONS);
		i = -1;
		while (++i < NUM_OF_ELEM_POSITIONS)
			rotate(&(object_type->current_positions[i]), &object_type->angle);
		elem = elem->next;
	}
	return ;
}
