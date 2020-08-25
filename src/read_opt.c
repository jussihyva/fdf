/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_opt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 14:14:32 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/25 13:00:24 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			read_opt(t_input *input, int *argc, char ***argv)
{
	while (*argc)
	{
		if (ft_strequ((*argv)[0], "-l"))
			input->opt |= e_leaks;
		else
			break ;
		ft_step_args(argc, argv);
	}
	return ;
}
