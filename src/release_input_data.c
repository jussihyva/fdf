/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_input_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:35:39 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/22 16:39:26 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		release_map_data(t_map *map)
{
	int			i;

	i = -1;
	if (map)
	{
		while (++i < map->map_size->y)
		{
			ft_memdel((void **)&map->object_type[i]);
			ft_memdel((void **)&map->elem_altitude[i]);
			ft_memdel((void **)&map->elem_color[i]);
		}
		ft_memdel((void **)&map->object_type);
		ft_memdel((void **)&map->elem_altitude);
		ft_memdel((void **)&map->elem_color);
		ft_memdel((void **)&map->map_size);
		ft_memdel((void **)&map);
	}
	return ;
}

void			release_input_data(t_input **input)
{
	int			i;

	release_map_data((*input)->map);
	ft_memdel((void **)&(*input)->cmd_args);
	ft_memdel((void **)&(*input)->angle);
	i = -1;
	while (++i < 6)
	{
		ft_memdel((void **)&(*input)->level_strings[i]);
		ft_memdel((void **)&(*input)->level_colors[i]);
	}
	ft_memdel((void **)&(*input)->level_strings);
	ft_memdel((void **)&(*input)->level_colors);
	ft_memdel((void **)input);
	return ;
}
