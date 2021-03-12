/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 01:33:27 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/12 12:16:40 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void				set_level_strings(const char **level_strings)
{
	level_strings[LOG_TRACE] = "TRACE";
	level_strings[LOG_DEBUG] = "DEBUG";
	level_strings[LOG_INFO] = "INFO";
	level_strings[LOG_WARN] = "WARN";
	level_strings[LOG_ERROR] = "ERROR";
	level_strings[LOG_FATAL] = "FATAL";
	return ;
}

static void				set_loging_parameters(t_input *input)
{
	input->level_strings =
				(const char **)ft_memalloc(sizeof(*input->level_strings) * 6);
	input->level_colors =
				(const char **)ft_memalloc(sizeof(*input->level_strings) * 6);
	set_level_strings(input->level_strings);
	input->level_colors[LOG_TRACE] = "\x1b[94m";
	input->level_colors[LOG_DEBUG] = "\x1b[36m";
	input->level_colors[LOG_INFO] = "\x1b[32m";
	input->level_colors[LOG_WARN] = "\x1b[33m";
	input->level_colors[LOG_ERROR] = "\x1b[31m";
	input->level_colors[LOG_FATAL] = "\x1b[35m";
	ft_log_set_params(input->level_strings, input->level_colors);

#ifdef LOGING_LEVEL

	ft_log_set_level(LOGING_LEVEL);

#else

	ft_log_set_level(LOG_ERROR);

#endif

	return ;
}

static int				open_fd(char *map_file_path)
{
	int		fd;

	if ((fd = open(map_file_path, O_RDONLY)) == -1)
	{
		ft_log_error("%s (%s) failed! errno=%d. %s: %s",
					"Opening of a file", map_file_path, errno, "Detail info",
					strerror(errno));
		ft_log_error("A map is mandatory input for fdf!");
		exit(42);
	}
	return (fd);
}

static void				validate_map_line(char *line, t_xy_values *map_size)
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

static t_map			*validate_map(char *map_file)
{
	t_map			*map;
	int				fd;
	char			*line;

	map = (t_map *)ft_memalloc(sizeof(*map));
	map->max_altitude = INT_MIN;
	map->min_altitude = INT_MAX;
	line = NULL;
	if ((fd = open_fd(map_file)) >= 0)
	{
		ft_printf("Map file path: %s\n", map_file);
		map->map_size =
				(t_xy_values *)ft_memalloc(sizeof(*map->map_size));
		while (ft_get_next_line(fd, &line) > 0)
		{
			ft_log_info("Line %3d: %s", map->map_size->y + 1, line);
			validate_map_line(line, map->map_size);
			map->map_size->y++;
			ft_strdel(&line);
		}
		ft_strdel(&line);
		close(fd);
	}
	return (map);
}

static int				*read_map_values(char *line, int size)
{
	int				*array;
	char			**char_array;
	int				i;
	char			*endptr;

	array = (int *)ft_memalloc(sizeof(*array) * size);
	i = -1;
	char_array = ft_strsplit(line, ' ');
	while (++i < size)
	{
		array[i] = ft_strtoi(char_array[i], &endptr, 10);
		ft_strdel(&char_array[i]);
	}
	ft_memdel((void **)&char_array);
	return (array);
}

static void				set_min_max_altitude(int line_index, t_map *map)
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

static void				read_content_of_map_file(int fd, t_map *map)
{
	char			*line;
	int				line_index;

	line_index = -1;
	while (ft_get_next_line(fd, &line) > 0)
	{
		line_index++;
		map->elem_altitude[line_index] =
										read_map_values(line, map->map_size->x);
		set_min_max_altitude(line_index, map);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

static t_map			*read_map_file(char *map_file)
{
	t_map			*map;
	int				fd;
	char			*line;

	line = NULL;
	map = validate_map(map_file);
	ft_log_info("Map size: X=%d Y=%d\n", map->map_size->x, map->map_size->y);
	fd = open_fd(map_file);
	map->elem_altitude = (int **)ft_memalloc(sizeof(*map->elem_altitude) *
												map->map_size->y);
	read_content_of_map_file(fd, map);
	if (!map->map_size->x)
	{
		ft_log_error("Empty file: %s", map_file);
		exit(42);
	}
	close(fd);
	return (map);
}

static t_position		*set_angle(int x, int y, int z)
{
	t_position		*angle;

	angle = (t_position *)ft_memalloc(sizeof(*angle));
	angle->x = ft_mod_int(x, 360);
	angle->y = ft_mod_int(y, 360);
	angle->z = ft_mod_int(z, 360);
	return (angle);
}

t_input					*read_cmd_arguments(int argc, char **argv)
{
	t_input		*input;

	input = (t_input *)ft_memalloc(sizeof(*input));
	set_loging_parameters(input);
	if ((input->cmd_args = argp_parse(argc, argv)))
	{
		if (input->cmd_args->map_file)
			input->map = read_map_file(input->cmd_args->map_file);
		if (input->cmd_args->projection_type)
		{
			if (input->cmd_args->projection_type == 2)
				input->angle = set_angle(-30, -45, 0);
			else if (input->cmd_args->projection_type == 3)
				input->angle = set_angle(-35, -45, 0);
			else
				input->angle = set_angle(0, 0, 0);
		}
		else
			input->angle = set_angle(input->cmd_args->x, input->cmd_args->y,
															input->cmd_args->z);
	}
	else
		release_input_data(&input);
	return (input);
}
