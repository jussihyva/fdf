/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 17:55:33 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/26 11:29:25 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		validata_array_size(t_point *point_array, int *array_size,
														int current_array_size)
{
	if (!(*array_size))
		*array_size = current_array_size;
	if (*array_size != current_array_size)
	{
		free(point_array);
		point_array = NULL;
	}
}

static t_point	create_point(char *s, char *end_ptr)
{
	t_point		point;
	char		*strtoi_end_ptr;

	bzero(&point, sizeof(point));
	strtoi_end_ptr = NULL;
	point.pos.z = ft_strtoi(s, &strtoi_end_ptr, 10);
	if (end_ptr != strtoi_end_ptr)
		point.pos.z = 0;
	return (point);
}

t_point			*parse_map_line(char *line, int *array_size)
{
	t_point			*point_array;
	char			sep;
	char			*start_ptr;
	char			*end_ptr;
	int				current_array_size;

	point_array = (t_point *)ft_memalloc(sizeof(*point_array) * 1000);
	sep = ' ';
	start_ptr = line;
	end_ptr = start_ptr;
	current_array_size = 0;
	while (end_ptr)
	{
		while (*start_ptr == sep)
			start_ptr++;
		if ((end_ptr = ft_strchr(start_ptr, sep)))
		{
			*end_ptr = '\0';
			point_array[current_array_size] = create_point(start_ptr, end_ptr);
			current_array_size++;
			start_ptr = end_ptr + 1;
		}
	}
	validata_array_size(point_array, array_size, current_array_size);
	return (point_array);
}
