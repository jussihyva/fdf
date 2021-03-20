/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 23:12:11 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/21 00:37:20 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			set_element_color(t_map *map, t_element *element,
																int elem_color)
{
	if (map->colors_from_map_file)
		element->color = elem_color;
	else
	{
		if (element->object_type->size.z)
			element->color = 0x00FF0000;
		else
			element->color = 0x000000FF;
	}
	return ;
}
