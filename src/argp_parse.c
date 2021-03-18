/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argp_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:28:12 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/18 10:24:24 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int			param_error(const char *error_string, const char s)
{
	ft_log_error(error_string, s);
	exit(42);
	return (0);
}

static int			save_args(void (fn)(t_cmd_args *, char, char *),
				t_cmd_args *cmd_args, char *arg, char *next_arg)
{
	char		opt;
	int			i;
	int			increase_arg_index;

	increase_arg_index = 0;
	i = 0;
	while ((opt = arg[i]))
	{
		if (ft_strchr("fPSFAxyz", opt))
		{
			if (next_arg)
			{
				fn(cmd_args, opt, next_arg);
				increase_arg_index++;
			}
			else
				param_error("Missing argument for parameter: -%c", opt);
			break ;
		}
		else
			param_error("Unknown parameter: -%c", opt);
		i++;
	}
	return (increase_arg_index);
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

t_cmd_args			*argp_parse(int argc, char **argv,
										void (fn)(t_cmd_args *, char, char *))
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
				arg_index += save_args(fn, cmd_args, &argv[arg_index][1],
											argv[arg_index + 1]);
			else
				arg_index += save_args(fn, cmd_args, &argv[arg_index][1], NULL);
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
