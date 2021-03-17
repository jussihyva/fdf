/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elemental_rotation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 20:46:08 by juhani            #+#    #+#             */
/*   Updated: 2021/03/17 07:56:46 by jkauppi          ###   ########.fr       */
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

static double	**get_z_rotation_matrix(int angle)
{
	static double	(*fn_z_rotation_matrix[3][3])(double) = {
													{cos, neg_sin, d_zero},
													{sin, cos, d_zero},
													{d_zero, d_zero, d_one}};
	double			**rotation_matrix;
	double			radian_angle;

	radian_angle = ft_radian(angle);
	if (!g_z_is_rotation_matrix[angle])
	{
		g_z_rotation_matrix[angle] = initialize_rotation_matrix(radian_angle,
														fn_z_rotation_matrix);
		g_z_is_rotation_matrix[angle] = 1;
	}
	rotation_matrix = g_z_rotation_matrix[angle];
	return (rotation_matrix);
}

static double	**get_y_rotation_matrix(int angle)
{
	static double	(*fn_y_rotation_matrix[3][3])(double) = {
													{cos, d_zero, sin},
													{d_zero, d_one, d_zero},
													{neg_sin, d_zero, cos}};
	double			**rotation_matrix;
	double			radian_angle;

	if (!g_y_is_rotation_matrix[angle])
	{
		radian_angle = ft_radian(angle);
		g_y_rotation_matrix[angle] = initialize_rotation_matrix(radian_angle,
														fn_y_rotation_matrix);
		g_y_is_rotation_matrix[angle] = 1;
	}
	rotation_matrix = g_y_rotation_matrix[angle];
	return (rotation_matrix);
}

static double	**get_x_rotation_matrix(int angle)
{
	static double	(*fn_x_rotation_matrix[3][3])(double) = {
													{d_one, d_zero, d_zero},
													{d_zero, cos, neg_sin},
													{d_zero, sin, cos}};
	double			**rotation_matrix;
	double			radian_angle;

	if (!g_x_is_rotation_matrix[angle])
	{
		radian_angle = ft_radian(angle);
		g_x_rotation_matrix[angle] = initialize_rotation_matrix(radian_angle,
														fn_x_rotation_matrix);
		g_x_is_rotation_matrix[angle] = 1;
	}
	rotation_matrix = g_x_rotation_matrix[angle];
	return (rotation_matrix);
}

static void		rotation(t_position *elem_position, t_position *angle)
{
	static size_t			vector_size = 3;
	static t_matrix_size	matrix_size = {3, 3};
	double					vector[vector_size];
	double					result_vector[vector_size];
	double					**rotation_matrix;

	vector[0] = (double)elem_position->x;
	vector[1] = (double)elem_position->y;
	vector[2] = (double)elem_position->z;
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
	elem_position->x = (int)(result_vector[0] + 0.5);
	elem_position->y = (int)(result_vector[1] + 0.5);
	elem_position->z = (int)(result_vector[2] + 0.5);
}

static size_t	line_len(t_position *elem_position1, t_position *elem_position2)
{
	double		len;

	len = sqrt(pow(elem_position1->x - elem_position2->x, 2) +
				pow(elem_position1->y - elem_position2->y, 2));
	return ((size_t)len);
}

static void		print_element_data(t_position *positions, t_position *angle)
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

void			elemental_rotation(t_position *current_positions,
								t_position *angle, t_position *position_offset,
													t_position *start_position)
{
	size_t		i;

	i = -1;
	while (++i < NUM_OF_ELEM_POSITIONS)
	{
		rotation(&(current_positions[i]), angle);
		position_offset->x = ft_max_int(position_offset->x,
													-(current_positions[i].x +
														start_position->x));
		position_offset->y = ft_max_int(position_offset->y,
													-(current_positions[i].y +
														start_position->y));
		position_offset->z = ft_max_int(position_offset->z,
													-(current_positions[i].z +
														start_position->z));
	}
	print_element_data(current_positions, angle);
	return ;
}
