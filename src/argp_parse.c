/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argp_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:28:12 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/12 11:40:59 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int			unknown_parameter(const char s)
{
	ft_log_error("Unknown parameter: -%c", s);
	exit(42);
	return (0);
}

static void			set_param_value(char opt, t_cmd_args *cmd_args,
																char *next_arg)
{
	if (opt == 'f')
		cmd_args->map_file = next_arg;
	else if (opt == 'P')
		cmd_args->projection_type = ft_atoi(next_arg);
	else if (opt == 'S')
		cmd_args->elem_side_len = ft_atoi(next_arg);
	else if (opt == 'F')
		cmd_args->altitude_factor = ft_atoi(next_arg);
	else if (opt == 'A')
		cmd_args->angle_steps = ft_atoi(next_arg);
	else if (opt == 'x')
		cmd_args->x = ft_atoi(next_arg);
	else if (opt == 'y')
		cmd_args->y = ft_atoi(next_arg);
	else if (opt == 'z')
		cmd_args->z = ft_atoi(next_arg);
}

static void			save_args(t_cmd_args *cmd_args, char *arg, char *next_arg,
																int *arg_index)
{
	char		opt;
	int			i;

	i = 0;
	while ((opt = arg[i]))
	{
		if (ft_strchr("fPSFAxyz", opt))
		{
			if (next_arg)
			{
				set_param_value(opt, cmd_args, next_arg);
				++(*arg_index);
			}
			else
			{
				ft_log_error("Missing argument for parameter: -%c", opt);
				exit(42);
			}
			break ;
		}
		else
			unknown_parameter(opt);
		i++;
	}
	return ;
}

static t_cmd_args	*initialize_cmd_args(void)
{
	t_cmd_args			*cmd_args;

	cmd_args = (t_cmd_args *)ft_memalloc(sizeof(*cmd_args));
	cmd_args->angle_steps = 5;
	cmd_args->altitude_factor = 1;
	cmd_args->elem_side_len = 20;
	return (cmd_args);
}

t_cmd_args			*argp_parse(int argc, char **argv)
{
	t_cmd_args			*cmd_args;
	int					arg_index;

	cmd_args = initialize_cmd_args();
	arg_index = 0;
	while (++arg_index < argc)
	{
		if (argv[arg_index][0] == '-')
		{
			if (argc > arg_index)
				save_args(cmd_args, &argv[arg_index][1], argv[arg_index + 1],
																	&arg_index);
			else
				save_args(cmd_args, &argv[arg_index][1], NULL, &arg_index);
		}
		else
		{
			ft_log_error("Unknown parameter: %c", argv[arg_index][0]);
			ft_log_error("  Note: The first character must be -");
			exit(42);
		}
	}
	return (cmd_args);
}
