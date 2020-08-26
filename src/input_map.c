/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 17:55:33 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/26 17:25:31 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		validata_array_size(t_point *point_array, int *array_size,
										int current_array_size, t_error *error)
{
	if (!*array_size)
		*array_size = current_array_size;
	if (*array_size != current_array_size)
	{
		free(point_array);
		point_array = NULL;
		*error = e_input_file_parse_error;
	}
	return ;
}

static t_point	create_point(char *s, char *end_ptr, t_error *error)
{
	t_point		point;
	char		*strtoi_end_ptr;

	bzero(&point, sizeof(point));
	strtoi_end_ptr = NULL;
	point.pos.z = ft_strtoi(s, &strtoi_end_ptr, 10);
	if (end_ptr != strtoi_end_ptr)
	{
		point.pos.z = 0;
		*error = e_input_file_parse_error;
	}
	return (point);
}

t_point			*parse_map_line(char *line, int *array_size, t_error *error)
{
	t_point			*point_array;
	char			*start_ptr;
	char			*end_ptr;
	int				current_array_size;

	point_array = (t_point *)ft_memalloc(sizeof(*point_array) * 1000);
	start_ptr = line;
	end_ptr = start_ptr;
	current_array_size = 0;
	while (end_ptr && !*error)
	{
		while (*start_ptr == MAP_FILE_PARAM_DELIMITER)
			start_ptr++;
		if ((end_ptr = ft_strchr(start_ptr, MAP_FILE_PARAM_DELIMITER)))
		{
			*end_ptr = '\0';
			point_array[current_array_size] = create_point(start_ptr, end_ptr,
																		error);
			current_array_size++;
			start_ptr = end_ptr + 1;
		}
	}
	validata_array_size(point_array, array_size, current_array_size, error);
	return (point_array);
}
