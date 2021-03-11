/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argp_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:28:12 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/11 22:25:23 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		save_args(t_cmd_args *cmd_args, char *arg, char *arg_next,
																		int *i)
{
	char		opt;
	int			j;

	j = 0;
	while ((opt = arg[++j]))
	{
		if (ft_strchr("fPSFAxyz", opt))
		{
			if (opt == 'f')
				cmd_args->map_file = arg_next;
			else if (opt == 'P')
				cmd_args->projection_type = ft_atoi(arg_next);
			else if (opt == 'S')
				cmd_args->elem_side_len = ft_atoi(arg_next);
			else if (opt == 'F')
				cmd_args->altitude_factor = ft_atoi(arg_next);
			else if (opt == 'A')
				cmd_args->angle_steps = ft_atoi(arg_next);
			else if (opt == 'x')
				cmd_args->x = ft_atoi(arg_next);
			else if (opt == 'y')
				cmd_args->y = ft_atoi(arg_next);
			else if (opt == 'z')
				cmd_args->z = ft_atoi(arg_next);
			++(*i);
			break ;
		}
		else
			ft_printf("-%c\n", opt);
	}
	return ;
}

static int		unknown_parameter(const char *s)
{
	ft_log_error("Unknown optional parameter: %s\n", s);
	exit(42);
	return (0);
}

t_cmd_args		*argp_parse(int argc, char **argv)
{
	t_cmd_args			*cmd_args;
	int					i;
	int					are_param_valid;

	cmd_args = (t_cmd_args *)ft_memalloc(sizeof(*cmd_args));
	are_param_valid = 1;
	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '-')
			save_args(cmd_args, argv[i], argv[i + 1], &i);
		else
			are_param_valid = unknown_parameter(argv[i]);
	}
	if (!are_param_valid)
		ft_memdel((void **)&cmd_args);
	return (cmd_args);
}
