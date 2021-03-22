/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 17:08:54 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/22 17:26:35 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int			read_map_values(char *line, int size,
										int **altitude_array, int **color_array)
{
	char			**input_array;
	int				i;
	char			*color_ptr;
	int				is_colors_included;

	is_colors_included = 0;
	*altitude_array = (int *)ft_memalloc(sizeof(*altitude_array) * size);
	*color_array = (int *)ft_memalloc(sizeof(*color_array) * size);
	i = -1;
	input_array = ft_strsplit(line, ' ');
	while (++i < size)
	{
		if ((color_ptr = ft_strchr(input_array[i], ',')))
			*color_ptr = '\0';
		(*altitude_array)[i] = read_altitude(input_array[i]);
		(*color_array)[i] = 0x8FFFFF;
		if (color_ptr)
		{
			(*color_array)[i] = read_color(color_ptr + 1);
			is_colors_included = 1;
		}
		ft_strdel(&input_array[i]);
	}
	ft_memdel((void **)&input_array);
	return (is_colors_included);
}

static void			read_content_of_map_file(int fd, t_map *map)
{
	char			*line;
	int				line_index;
	int				**altitude_array;
	int				**color_array;

	map->elem_altitude = (int **)ft_memalloc(sizeof(*map->elem_altitude) *
												map->map_size->y);
	map->elem_color = (int **)ft_memalloc(sizeof(*map->elem_color) *
												map->map_size->y);
	line_index = -1;
	line = NULL;
	while (ft_get_next_line(fd, &line) > 0)
	{
		line_index++;
		altitude_array = &map->elem_altitude[line_index];
		color_array = &map->elem_color[line_index];
		map->colors_from_map_file |= read_map_values(line, map->map_size->x,
												altitude_array, color_array);
		set_min_max_altitude(line_index, map);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return ;
}

static void			validate_map_line(char *line, t_xy_values_old *map_size)
{
	char			**char_array;
	int				i;

	i = -1;
	char_array = ft_strsplit(line, ' ');
	while (char_array[++i])
	{
		ft_strdel(&char_array[i]);
	}
	ft_memdel((void **)&char_array);
	if (map_size->x == 0)
		map_size->x = i;
	else
	{
		if (map_size->x != i)
		{
			ft_printf("%s %s %d and %d.\n",
						"ERROR: Variable num of numbers in map lines. ",
						"Compare lines ",
						map_size->y,
						map_size->y + 1);
			exit(42);
		}
	}
	return ;
}

static t_map		*validate_map(char *map_file)
{
	t_map			*map;
	int				fd;
	char			*line;

	map = (t_map *)ft_memalloc(sizeof(*map));
	map->max_altitude = INT_MIN;
	map->min_altitude = INT_MAX;
	if ((fd = open_fd(map_file)) >= 0)
	{
		line = NULL;
		ft_printf("Map file path: %s\n", map_file);
		map->map_size =
				(t_xy_values_old *)ft_memalloc(sizeof(*map->map_size));
		while (ft_get_next_line(fd, &line) > 0)
		{
			ft_log_debug("Line %3d: %s", map->map_size->y + 1, line);
			validate_map_line(line, map->map_size);
			map->map_size->y++;
			ft_strdel(&line);
		}
		ft_strdel(&line);
		close(fd);
	}
	return (map);
}

t_map				*read_map_file(char *map_file)
{
	t_map			*map;
	int				fd;
	char			*line;

	line = NULL;
	map = validate_map(map_file);
	ft_log_info("Map size: X=%d Y=%d", map->map_size->x, map->map_size->y);
	if (map_file)
		fd = open_fd(map_file);
	else
		fd = 0;
	read_content_of_map_file(fd, map);
	if (!map->map_size->x)
	{
		ft_log_error("Empty file: %s", map_file);
		exit(42);
	}
	close(fd);
	return (map);
}
