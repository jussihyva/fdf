/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 17:18:00 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/22 17:21:54 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			read_altitude(char *ptr)
{
	int		altitude;
	char	*remainings;

	altitude = ft_strtoi(ptr, &remainings, 10);
	if (*remainings)
	{
		ft_log_error("%s %s \"%s\"",
							"A map file includes invalid parameter.",
							"Type of a value should be INT but now it is",
							ptr);
		exit(42);
	}
	return (altitude);
}

int			read_color(char *ptr)
{
	int		color;
	char	*remainings;

	color = ft_strtoi(ptr, &remainings, 16);
	if (*remainings)
	{
		ft_log_error("%s %s \"%s\"",
							"A map file includes invalid parameter.",
							"Type of a value should be HEX but now it is",
							ptr);
		exit(42);
	}
	return (color);
}

void		set_min_max_altitude(int line_index, t_map *map)
{
	int				j;

	j = -1;
	while (++j < map->map_size->x)
	{
		map->min_altitude = ft_min_int(map->max_altitude,
											map->elem_altitude[line_index][j]);
		map->max_altitude = ft_max_int(map->max_altitude,
											map->elem_altitude[line_index][j]);
	}
}

int			open_fd(char *map_file_path)
{
	int		fd;

	fd = 0;
	if (map_file_path)
	{
		if ((fd = open(map_file_path, O_RDONLY)) == -1)
		{
			ft_log_error("%s (%s) failed! errno=%d. %s: %s",
					"Opening of a file", map_file_path, errno, "Detail info",
															strerror(errno));
			ft_log_error("A map is mandatory input for fdf!");
			exit(42);
		}
	}
	return (fd);
}
