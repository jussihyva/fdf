/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 09:34:40 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/22 10:12:25 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	conv_str_to_int(const char opt, const char *s)
{
	char		*remainings;
	int			value;

	value = ft_strtoi(s, &remainings, 10);
	if (*remainings || errno != 0)
	{
		ft_log_error("Not valid parameter value -%c %s", opt, s);
		exit(42);
	}
	return (value);
}

void		save_cmd_arguments(t_cmd_args *cmd_args, char opt, char *next_arg)
{
	if (opt == 'f')
		cmd_args->map_file = next_arg;
	else if (opt == 'M')
		cmd_args->drawing_mode = conv_str_to_int(opt, next_arg);
	else if (opt == 'L')
		cmd_args->loging_level = conv_str_to_int(opt, next_arg);
	else if (opt == 'P')
		cmd_args->projection_type = conv_str_to_int(opt, next_arg);
	else if (opt == 'S')
		cmd_args->elem_side_len = conv_str_to_int(opt, next_arg);
	else if (opt == 'F')
		cmd_args->altitude_factor = conv_str_to_int(opt, next_arg);
	else if (opt == 'A')
		cmd_args->angle_steps = conv_str_to_int(opt, next_arg);
	else if (opt == 'x')
		cmd_args->x = conv_str_to_int(opt, next_arg);
	else if (opt == 'y')
		cmd_args->y = conv_str_to_int(opt, next_arg);
	else if (opt == 'z')
		cmd_args->z = conv_str_to_int(opt, next_arg);
	return ;
}
