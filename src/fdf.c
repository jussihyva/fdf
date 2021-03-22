/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 04:03:20 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/22 19:42:21 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			data_from_cmd_params(t_mlx_win *mlx_win, t_input *input)
{
	mlx_win->img_size.x = 5000;
	mlx_win->img_size.y = 5000;
	mlx_win->angle = input->angle;
	mlx_win->drawing_mode = input->cmd_args->drawing_mode;
	ft_log_info("Start angle: x=%.0f, y=%.0f z=%.0f\n", mlx_win->angle->x,
										mlx_win->angle->y, mlx_win->angle->z);
	mlx_win->angle_step = input->cmd_args->angle_steps;
	mlx_win->element_map_size = input->map->map_size;
	return ;
}

static t_element	***initialize_elem_table(t_xy_values_old *map_size)
{
	t_element	***elem_table;
	int			i;

	elem_table = (t_element ***)ft_memalloc(sizeof(*elem_table) * map_size->y);
	i = -1;
	while (++i < map_size->y)
		elem_table[i] = (t_element **)ft_memalloc(sizeof(*elem_table[i]) *
																map_size->x);
	return (elem_table);
}

static t_mlx_win	*initialize_mlx_win(t_input *input)
{
	t_mlx_win			*mlx_win;

	mlx_win = (t_mlx_win *)ft_memalloc(sizeof(*mlx_win));
	data_from_cmd_params(mlx_win, input);
	mlx_win->img_position_offset =
			(t_xyz_values *)ft_memalloc(sizeof(*mlx_win->img_position_offset));
	mlx_win->img_start_position =
				(t_position *)ft_memalloc(sizeof(*mlx_win->img_start_position));
	mlx_win->render_action = e_no_action;
	mlx_win->img_line_lst =
						(t_list **)ft_memalloc(sizeof(*mlx_win->img_line_lst));
	mlx_win->object_type_lst =
					(t_list **)ft_memalloc(sizeof(*mlx_win->object_type_lst));
	create_object_types(mlx_win->object_type_lst, input->map, input);
	mlx_win->mlx = mlx_init();
	initialize_window(mlx_win, "FDF project (free running)");
	mlx_win->empty_img = mlx_new_image(mlx_win->mlx, mlx_win->img_size.x,
														mlx_win->img_size.y);
	mlx_win->img = mlx_new_image(mlx_win->mlx, mlx_win->img_size.x,
														mlx_win->img_size.y);
	mlx_win->elem_table = initialize_elem_table(input->map->map_size);
	return (mlx_win);
}

static void			print_input_map(int **elem_altitude, t_map *map)
{
	int			i;
	int			j;

	i = -1;
	while (++i < map->map_size->y)
	{
		j = -1;
		while (++j < map->map_size->x)
			ft_log_trace(" %3d", elem_altitude[i][j]);
	}
	return ;
}

int					main(int argc, char **argv)
{
	t_mlx_win			*mlx_win;
	t_xyz_values		elem_start_position;
	t_input				*input;

	if (!(input = read_cmd_arguments(argc, argv)))
		return (42);
	mlx_win = initialize_mlx_win(input);
	print_input_map(input->map->elem_altitude, input->map);
	set_position(&elem_start_position, 0, 0, 0);
	ft_memcpy(mlx_win->img_start_position, &elem_start_position,
										sizeof(*mlx_win->img_start_position));
	rotate_objects(mlx_win->object_type_lst, input->angle);
	create_elements(input->map, mlx_win->elem_table, mlx_win);
	if (mlx_win->drawing_mode == 2)
		draw_lines(mlx_win);
	else
		draw_img_lines(mlx_win);
	mlx_win->render_action = e_put_image_to_window;
	mlx_loop_hook(mlx_win->mlx, render_frame, mlx_win);
	mlx_loop(mlx_win->mlx);
	release_mlx_win(&mlx_win);
	release_input_data(&input);
	return (0);
}
