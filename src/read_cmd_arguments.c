/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 01:33:27 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/24 00:47:22 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void				set_level_strings(const char **level_strings)
{
	level_strings[LOG_TRACE] = ft_strdup("TRACE");
	level_strings[LOG_DEBUG] = ft_strdup("DEBUG");
	level_strings[LOG_INFO] = ft_strdup("INFO");
	level_strings[LOG_WARN] = ft_strdup("WARN");
	level_strings[LOG_ERROR] = ft_strdup("ERROR");
	level_strings[LOG_FATAL] = ft_strdup("FATAL");
	return ;
}

static void				set_loging_parameters(t_input *input)
{
	input->level_strings =
				(const char **)ft_memalloc(sizeof(*input->level_strings) * 6);
	input->level_colors =
				(const char **)ft_memalloc(sizeof(*input->level_strings) * 6);
	set_level_strings(input->level_strings);
	input->level_colors[LOG_TRACE] = ft_strdup("\x1b[94m");
	input->level_colors[LOG_DEBUG] = ft_strdup("\x1b[36m");
	input->level_colors[LOG_INFO] = ft_strdup("\x1b[32m");
	input->level_colors[LOG_WARN] = ft_strdup("\x1b[33m");
	input->level_colors[LOG_ERROR] = ft_strdup("\x1b[31m");
	input->level_colors[LOG_FATAL] = ft_strdup("\x1b[35m");
	ft_log_set_params(input->level_strings, input->level_colors);
	ft_log_set_level(LOG_ERROR);
	return ;
}

static t_xyz_values		*set_angle(int x, int y, int z)
{
	t_xyz_values		*angle;

	angle = (t_xyz_values *)ft_memalloc(sizeof(*angle));
	angle->x = (double)ft_mod_int(x, 360);
	angle->y = (double)ft_mod_int(y, 360);
	angle->z = (double)ft_mod_int(z, 360);
	return (angle);
}

static t_xyz_values		*prepare_projection_params(t_cmd_args *cmd_args)
{
	t_xyz_values		*angle;

	if (cmd_args->projection_type)
	{
		if (!cmd_args->altitude_factor)
			cmd_args->altitude_factor = 1;
		if (cmd_args->projection_type == 2)
			angle = set_angle(-30, -45, 0);
		else if (cmd_args->projection_type == 3)
			angle = set_angle(-35, -45, 0);
		else if (cmd_args->projection_type == 4)
			angle = set_angle(90, 0, 0);
		else
			angle = set_angle(0, 0, 0);
	}
	else
		angle = set_angle(cmd_args->x, cmd_args->y, cmd_args->z);
	return (angle);
}

t_input					*read_cmd_arguments(int argc, char **argv)
{
	t_input		*input;

	input = (t_input *)ft_memalloc(sizeof(*input));
	set_loging_parameters(input);
	if ((input->cmd_args = argp_parse(argc, argv, save_cmd_arguments)))
	{
		ft_log_set_level(input->cmd_args->loging_level);
		input->map = read_map_file(input->cmd_args->map_file);
		input->angle = prepare_projection_params(input->cmd_args);
		calculate_object_size(input, &input->object_xy_size);
	}
	else
		release_input_data(&input);
	ft_log_info("Map file: %s", input->cmd_args->map_file);
	ft_log_info("Protection type: %d", input->cmd_args->projection_type);
	return (input);
}
