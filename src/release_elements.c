/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_elements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:42:00 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/23 08:45:14 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		release_element(t_element **element)
{
	if (*element)
	{
		ft_memdel((void **)&(*element)->start_position);
		ft_memdel((void **)&(*element)->elem_lines);
		ft_memdel((void **)&(*element)->angle);
		ft_memdel((void **)element);
	}
	return ;
}

void			release_elements(t_xy_values_int *element_map_size,
														t_element ***elem_table)
{
	int			i;
	int			j;

	i = -1;
	while (++i < element_map_size->y)
	{
		j = -1;
		while (++j < element_map_size->x)
			release_element(&elem_table[i][j]);
		ft_memdel((void **)&elem_table[i]);
	}
	return ;
}
