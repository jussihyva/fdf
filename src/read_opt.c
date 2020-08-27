/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_opt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 14:14:32 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/27 17:07:54 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		set_window_size(int *argc, char ***argv)
{
	char		*end_ptr;
	int			size;

	end_ptr = NULL;
	ft_step_args(argc, argv);
	size = ft_strtoi(*argv[0], &end_ptr, 10);
	return (size);
}

void			read_opt(t_input *input, int *argc, char ***argv)
{
	while (*argc)
	{
		if (ft_strequ((*argv)[0], "-l"))
			input->opt |= e_leaks;
		else if (ft_strequ((*argv)[0], "-t"))
			input->opt |= e_test;
		else if (ft_strequ((*argv)[0], "-w"))
			input->width = set_window_size(argc, argv);
		else if (ft_strequ((*argv)[0], "-h"))
			input->hight = set_window_size(argc, argv);
		else if (ft_strequ((*argv)[0], "-f"))
			save_input_file(input, argc, argv);
		else
			break ;
		ft_step_args(argc, argv);
	}
	return ;
}
