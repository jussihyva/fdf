/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_functions_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:23:11 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/23 09:21:29 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
					(double *)ft_memalloc(sizeof(*rotation_matrix[i]) * 3);
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

double			**get_z_rotation_matrix(t_mlx_win *mlx_win, double angle)
{
	static double	(*fn_z_rotation_matrix[3][3])(double) = {
													{cos, neg_sin, d_zero},
													{sin, cos, d_zero},
													{d_zero, d_zero, d_one}};
	double			**rotation_matrix;
	double			radian_angle;

	radian_angle = ft_radian(angle);
	if ((angle == (double)((int)angle)) &&
								(!mlx_win->z_is_rotation_matrix[(int)angle]))
	{
		mlx_win->z_rotation_matrix[(int)angle] =
				initialize_rotation_matrix(radian_angle, fn_z_rotation_matrix);
		mlx_win->z_is_rotation_matrix[(int)angle] = 1;
	}
	rotation_matrix = mlx_win->z_rotation_matrix[(int)angle];
	return (rotation_matrix);
}

double			**get_y_rotation_matrix(t_mlx_win *mlx_win, double angle)
{
	static double	(*fn_y_rotation_matrix[3][3])(double) = {
													{cos, d_zero, sin},
													{d_zero, d_one, d_zero},
													{neg_sin, d_zero, cos}};
	double			**rotation_matrix;
	double			radian_angle;

	if ((angle == (double)((int)angle)) &&
								(!mlx_win->y_is_rotation_matrix[(int)angle]))
	{
		radian_angle = ft_radian(angle);
		mlx_win->y_rotation_matrix[(int)angle] =
				initialize_rotation_matrix(radian_angle, fn_y_rotation_matrix);
		mlx_win->y_is_rotation_matrix[(int)angle] = 1;
	}
	rotation_matrix = mlx_win->y_rotation_matrix[(int)angle];
	return (rotation_matrix);
}

double			**get_x_rotation_matrix(t_mlx_win *mlx_win, double angle)
{
	static double	(*fn_x_rotation_matrix[3][3])(double) = {
													{d_one, d_zero, d_zero},
													{d_zero, cos, neg_sin},
													{d_zero, sin, cos}};
	double			**rotation_matrix;
	double			radian_angle;

	if ((angle == (double)((int)angle)) &&
								(!mlx_win->x_is_rotation_matrix[(int)angle]))
	{
		radian_angle = ft_radian(angle);
		mlx_win->x_rotation_matrix[(int)angle] =
				initialize_rotation_matrix(radian_angle, fn_x_rotation_matrix);
		mlx_win->x_is_rotation_matrix[(int)angle] = 1;
	}
	rotation_matrix = mlx_win->x_rotation_matrix[(int)angle];
	return (rotation_matrix);
}
