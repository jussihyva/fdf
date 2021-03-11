/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 04:03:20 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/11 18:37:12 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			set_loging_parameters(void)
{
	static const char *level_strings[6];
	static const char *level_colors[6];

	level_strings[LOG_TRACE] = "TRACE";
	level_strings[LOG_DEBUG] = "DEBUG";
	level_strings[LOG_INFO] = "INFO";
	level_strings[LOG_WARN] = "WARN";
	level_strings[LOG_ERROR] = "ERROR";
	level_strings[LOG_FATAL] = "FATAL";
	level_colors[LOG_TRACE] = "\x1b[94m";
	level_colors[LOG_DEBUG] = "\x1b[36m";
	level_colors[LOG_INFO] = "\x1b[32m";
	level_colors[LOG_WARN] = "\x1b[33m";
	level_colors[LOG_ERROR] = "\x1b[31m";
	level_colors[LOG_FATAL] = "\x1b[35m";

	ft_log_set_params(level_strings, level_colors);
#ifdef LOGING_LEVEL
	ft_log_set_level(LOGING_LEVEL);
#else
	ft_log_set_level(LOG_ERROR);
#endif
	return ;
}

static t_element	***create_element_map(t_mlx_win *mlx_win, t_map *map)
{
	t_element		***element_map;
	t_position		*elem_start_position;
	t_position		elem_size;
	t_position		*position_offset;
	int				i;
	int				j;

	mlx_win->first_elem_start_position =
		(t_position *)ft_memalloc(sizeof(*mlx_win->first_elem_start_position));
	set_position(mlx_win->first_elem_start_position, 0, 0, 0);
	position_offset = (t_position *)ft_memalloc(sizeof(*position_offset));
	set_position(&elem_size, 25, 25, 25);
	element_map = (t_element ***)ft_memalloc(sizeof(*element_map) *
													map->map_size->y);
	i = -1;
	elem_start_position = mlx_win->first_elem_start_position;
	while (++i < map->map_size->y)
	{
		element_map[i] = (t_element **)ft_memalloc(sizeof(*element_map[i]) *
													map->map_size->x);
		j = -1;
		while (++j < map->map_size->x)
		{
			element_map[i][j] = create_element(mlx_win, elem_start_position,
												position_offset, &elem_size);
			elem_start_position = &element_map[i][j]->current_positions[1];
		}
		elem_start_position = &element_map[i][0]->current_positions[2];
	}
	ft_memdel((void **)&position_offset);
	return (element_map);
}

int					main(int argc, char **argv)
{
	t_mlx_win			*mlx_win;
	t_position			elem_start_position;
	t_position			elem_size;
	t_position			*position_offset;
	t_input				*input;
	int					**elem_altitude;
	int					i;
	int					j;
	int					z;

	set_loging_parameters();
	if (!(input = read_cmd_arguments(argc, argv)))
		return (42);
	ft_log_info("Map file: %s", input->cmd_args->map_file);
	ft_log_info("Protection type: %d", input->cmd_args->projection_type);
	position_offset = (t_position *)ft_memalloc(sizeof(*position_offset));
	mlx_win = (t_mlx_win *)ft_memalloc(sizeof(*mlx_win));
	mlx_win->img_size.x = 4000;
	mlx_win->img_size.y = 4000;
	mlx_win->img_start_position =
				(t_position *)ft_memalloc(sizeof(*mlx_win->img_start_position));
	mlx_win->render_action = e_no_action;
	mlx_win->angle = input->angle;
	ft_printf("Start angle: x=%d, y=%d z=%d\n", mlx_win->angle->x, mlx_win->angle->y, mlx_win->angle->z);
	mlx_win->angle_step = input->cmd_args->angle_steps;
	elem_altitude = input->map->elem_altitude;
	mlx_win->element_map = create_element_map(mlx_win, input->map);
	mlx_win->element_map_size = input->map->map_size;
	i = -1;
	while (++i < input->map->map_size->y)
	{
		j = -1;
		while (++j < input->map->map_size->x)
			ft_printf(" %3d", elem_altitude[i][j]);
		ft_printf("\n");
	}
	mlx_win->mlx = mlx_init();
	initialize_window(mlx_win, "Minilibx training 4 (ex4)");
	mlx_win->empty_img = mlx_new_image(mlx_win->mlx, mlx_win->img_size.x, mlx_win->img_size.y);
	mlx_win->img = mlx_new_image(mlx_win->mlx, mlx_win->img_size.x, mlx_win->img_size.y);
	mlx_win->elem_table = (t_element ***)ft_memalloc(sizeof(**mlx_win->elem_table)
													* input->map->map_size->y);
	i = -1;
	while (++i < input->map->map_size->y)
	{
		mlx_win->elem_table[i] = (t_element **)ft_memalloc(
				sizeof(*mlx_win->elem_table[i]) * input->map->map_size->x);
	}
	set_position(&elem_start_position, 0, 0, 0);
	ft_memcpy(mlx_win->img_start_position, &elem_start_position,
											sizeof(*mlx_win->img_start_position));
	ft_printf("Map size x=%d\n", input->map->map_size->x);
	ft_printf("Map size y=%d\n", input->map->map_size->y);
	i = -1;
	while (++i < input->map->map_size->y)
	{
		j = -1;
		while (++j < input->map->map_size->x)
		{
			z = input->map->elem_altitude[i][j] * input->cmd_args->altitude_factor;
			set_position(&elem_size, input->cmd_args->elem_side_len, input->cmd_args->elem_side_len, z);
			mlx_win->elem_table[i][j] = create_element(mlx_win, &elem_start_position,
														position_offset, &elem_size);
			ft_memcpy(&elem_start_position, mlx_win->elem_table[i][j]->start_position, sizeof(elem_start_position));
			elem_start_position.x += mlx_win->elem_table[i][j]->current_positions[1].x;
			elem_start_position.y += mlx_win->elem_table[i][j]->current_positions[1].y;
		}
		elem_start_position.x = mlx_win->elem_table[i][0]->current_positions[2].x * (i + 1);
		elem_start_position.y = mlx_win->elem_table[i][0]->current_positions[2].y * (i + 1);
	}
	i = -1;
	while (++i < input->map->map_size->y)
	{
		j = -1;
		while (++j < input->map->map_size->x)
		{
			mlx_win->elem_table[i][j]->elem_position_offset.x = position_offset->x + mlx_win->elem_table[i][j]->start_position->x;
			mlx_win->elem_table[i][j]->elem_position_offset.y = position_offset->y + mlx_win->elem_table[i][j]->start_position->y;
			draw_lines(mlx_win->img, mlx_win->elem_table[i][j]);
		}
	}
	mlx_win->render_action = e_put_image_to_window;
	mlx_loop_hook(mlx_win->mlx, render_frame, mlx_win);
	mlx_loop(mlx_win->mlx);
	release_mlx_win(&mlx_win);
	release_input_data(&input);
	ft_memdel((void **)&position_offset);
	return (0);
}
