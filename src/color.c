/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 23:12:11 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/21 09:01:35 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			get_element_color(t_map *map, t_object_type *object_type,
																int elem_color)
{
	int		color;

	if (map->colors_from_map_file)
		color = elem_color;
	else
		color = (object_type->size.z) ? 0x00FF0000 : 0x000000FF;
	return (color);
}
