/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 01:33:27 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/20 09:33:24 by jkauppi          ###   ########.fr       */
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
	ft_log_set_level(LOG_ERROR);
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

static void				validate_map_line(char *line, t_xy_values_old *map_size)
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

static int				read_altitude(char *ptr)
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

static int				read_color(char *ptr)
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

static int				read_map_values(char *line, int size,
										int **altitude_array, int **color_array)
{
	char			**input_array;
	int				i;
	char			*color_ptr;
	int				is_colors_included;

	is_colors_included = 0;
	*altitude_array = (int *)ft_memalloc(sizeof(**altitude_array) * size);
	*color_array = (int *)ft_memalloc(sizeof(**color_array) * size);
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
	int				**altitude_array;
	int				**color_array;

	map->elem_altitude = (int **)ft_memalloc(sizeof(*map->elem_altitude) *
												map->map_size->y);
	map->elem_color = (int **)ft_memalloc(sizeof(*map->elem_color) *
												map->map_size->y);
	line_index = -1;
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

static t_map			*read_map_file(char *map_file)
{
	t_map			*map;
	int				fd;
	char			*line;

	line = NULL;
	map = validate_map(map_file);
	ft_log_info("Map size: X=%d Y=%d", map->map_size->x, map->map_size->y);
	fd = open_fd(map_file);
	read_content_of_map_file(fd, map);
	if (!map->map_size->x)
	{
		ft_log_error("Empty file: %s", map_file);
		exit(42);
	}
	close(fd);
	return (map);
}

static t_xyz_values		*set_angle(int x, int y, int z)
{
	t_xyz_values		*angle;

	angle = (t_xyz_values *)ft_memalloc(sizeof(*angle));
	angle->x = (double)ft_mod_int(x, 360);
	angle->y = (double)ft_mod_int(y, 360);
	angle->z = (double)ft_mod_int(z, 360);
	return (angle);
}

static void				calculate_object_xy_size(t_xy_values *object_xy_size,
														t_cmd_args *cmd_args)
{
	object_xy_size->x = (double)cmd_args->elem_side_len;
	object_xy_size->y = (double)cmd_args->elem_side_len;
	return ;
}

static t_xyz_values		*prepare_projection_params(t_cmd_args *cmd_args)
{
	t_xyz_values		*angle;

	if (cmd_args->projection_type)
	{
		if (cmd_args->projection_type == 2)
			angle = set_angle(-30, -45, 0);
		else if (cmd_args->projection_type == 3)
			angle = set_angle(-35, -45, 0);
		else
			angle = set_angle(0, 0, 0);
	}
	else
		angle = set_angle(cmd_args->x, cmd_args->y, cmd_args->z);
	return (angle);
}

t_input					*read_cmd_arguments(int argc, char **argv)
{
	t_input		*input;

	input = (t_input *)ft_memalloc(sizeof(*input));
	set_loging_parameters(input);
	if ((input->cmd_args = argp_parse(argc, argv, save_cmd_arguments)))
	{
		ft_log_set_level(input->cmd_args->logging_level);
		if (input->cmd_args->map_file)
			input->map = read_map_file(input->cmd_args->map_file);
		input->angle = prepare_projection_params(input->cmd_args);
		calculate_object_xy_size(&input->object_xy_size, input->cmd_args);
	}
	else
		release_input_data(&input);
	return (input);
}
