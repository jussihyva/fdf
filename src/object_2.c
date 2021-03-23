/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:59:49 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/24 00:13:47 by jkauppi          ###   ########.fr       */
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

static int		set_altitude_factor(t_cmd_args *cmd_args, double max_altitude)
{
	int		alt_factor;

	alt_factor = (int)(1000 / sqrt(3) / max_altitude);
	if (cmd_args->altitude_factor)
	{
		if (alt_factor < cmd_args->altitude_factor)
		{
			ft_log_error("Maximun value for altitude factor (-F) is %d",
																	alt_factor);
			exit(42);
		}
		alt_factor = cmd_args->altitude_factor;
	}
	return (alt_factor);
}

static void		set_object_size(t_xy_values *obj_size, t_input *input)
{
	obj_size->x = 1000 / sqrt(3) / ft_max_double(input->map->map_size->x,
													input->map->map_size->x);
	obj_size->y = obj_size->x;
	if (input->cmd_args->elem_side_len)
	{
		if (obj_size->x < input->cmd_args->elem_side_len)
		{
			ft_log_error("Maximun value for element size (-S) is %d",
															(int)obj_size->y);
			exit(42);
		}
		obj_size->x = input->cmd_args->elem_side_len;
		obj_size->y = obj_size->x;
	}
	return ;
}

void			calculate_object_size(t_input *input, t_xy_values *obj_size)
{
	t_map				*map;
	double				max_altitude;

	map = input->map;
	max_altitude = map->max_altitude > 0 ? map->max_altitude : 0;
	max_altitude += map->min_altitude < 0 ? ft_abs(map->min_altitude) : 0;
	set_object_size(obj_size, input);
	map->alt_factor = set_altitude_factor(input->cmd_args, max_altitude);
	ft_log_info("Object size calculation");
	ft_log_info("Altitude factor: %d", input->cmd_args->altitude_factor);
	ft_log_info("Map size: X=%d Y=%d Z=%d", map->map_size->x, map->map_size->y,
															(int)max_altitude);
	ft_log_info("Max element size: X=%d Y=%d", (int)obj_size->x,
															(int)obj_size->y);
	return ;
}
