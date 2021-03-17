/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elemental_rotation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 20:46:08 by juhani            #+#    #+#             */
/*   Updated: 2021/03/17 18:54:58 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double	d_one(double nbr)
{
	(void)nbr;
	return ((double)1);
}

static double	d_zero(double nbr)
{
	(void)nbr;
	return ((double)0);
}

static double	neg_sin(double nbr)
{
	return (-sin(nbr));
}

static double	**initialize_rotation_matrix(double radian_angle,
									double (*fn_rotation_matrix[3][3])(double))
{
	double		**rotation_matrix;
	size_t		i;
	size_t		j;

	rotation_matrix = (double **)ft_memalloc(sizeof(*rotation_matrix) * 3);
	i = -1;
	while (++i < 3)
		rotation_matrix[i] =
					(double *)ft_memalloc(sizeof(**rotation_matrix) * 3);
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			rotation_matrix[i][j] +=
								(*fn_rotation_matrix[i][j])(radian_angle);
	}
	return (rotation_matrix);
}

static double	**get_z_rotation_matrix(double angle)
{
	static double	(*fn_z_rotation_matrix[3][3])(double) = {
													{cos, neg_sin, d_zero},
													{sin, cos, d_zero},
													{d_zero, d_zero, d_one}};
	double			**rotation_matrix;
	double			radian_angle;

	radian_angle = ft_radian(angle);
	if ((angle == (double)((int)angle)) &&
										(!g_z_is_rotation_matrix[(int)angle]))
	{
		g_z_rotation_matrix[(int)angle] =
				initialize_rotation_matrix(radian_angle, fn_z_rotation_matrix);
		g_z_is_rotation_matrix[(int)angle] = 1;
	}
	rotation_matrix = g_z_rotation_matrix[(int)angle];
	return (rotation_matrix);
}

static double	**get_y_rotation_matrix(double angle)
{
	static double	(*fn_y_rotation_matrix[3][3])(double) = {
													{cos, d_zero, sin},
													{d_zero, d_one, d_zero},
													{neg_sin, d_zero, cos}};
	double			**rotation_matrix;
	double			radian_angle;

	if ((angle == (double)((int)angle)) &&
										(!g_y_is_rotation_matrix[(int)angle]))
	{
		radian_angle = ft_radian(angle);
		g_y_rotation_matrix[(int)angle] =
				initialize_rotation_matrix(radian_angle, fn_y_rotation_matrix);
		g_y_is_rotation_matrix[(int)angle] = 1;
	}
	rotation_matrix = g_y_rotation_matrix[(int)angle];
	return (rotation_matrix);
}

static double	**get_x_rotation_matrix(double angle)
{
	static double	(*fn_x_rotation_matrix[3][3])(double) = {
													{d_one, d_zero, d_zero},
													{d_zero, cos, neg_sin},
													{d_zero, sin, cos}};
	double			**rotation_matrix;
	double			radian_angle;

	if ((angle == (double)((int)angle)) &&
										(!g_x_is_rotation_matrix[(int)angle]))
	{
		radian_angle = ft_radian(angle);
		g_x_rotation_matrix[(int)angle] =
				initialize_rotation_matrix(radian_angle, fn_x_rotation_matrix);
		g_x_is_rotation_matrix[(int)angle] = 1;
	}
	rotation_matrix = g_x_rotation_matrix[(int)angle];
	return (rotation_matrix);
}

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

static size_t	line_len(t_xyz_values *elem_position1,
												t_xyz_values *elem_position2)
{
	double		len;

	len = sqrt(pow(elem_position1->x - elem_position2->x, 2) +
				pow(elem_position1->y - elem_position2->y, 2));
	return ((size_t)len);
}

static void		print_element_data(t_xyz_values *positions, t_xyz_values *angle)
{
	size_t		size54;
	size_t		size57;
	size_t		size51;

	(void)angle;
	size54 = line_len(&positions[5], &positions[4]);
	size57 = line_len(&positions[7], &positions[5]);
	size51 = line_len(&positions[1], &positions[5]);
	return ;
}

void			elemental_rotation(t_xyz_values *current_positions,
							t_xyz_values *angle, t_xyz_values *position_offset,
												t_xyz_values *start_position)
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
	print_element_data(current_positions, angle);
	return ;
}

void			rotate_objects(t_list **object_type_lst, t_xyz_values *angle)
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
