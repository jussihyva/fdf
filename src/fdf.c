/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 04:03:20 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/22 09:01:42 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int					main(int argc, char **argv)
{
	t_mlx_win			*mlx_win;
	t_xyz_values		elem_start_position;
	t_input				*input;
	int					**elem_altitude;
	int					i;
	int					j;

	if (!(input = read_cmd_arguments(argc, argv)))
		return (42);
	ft_log_info("Map file: %s", input->cmd_args->map_file);
	ft_log_info("Protection type: %d", input->cmd_args->projection_type);
	mlx_win = (t_mlx_win *)ft_memalloc(sizeof(*mlx_win));
	mlx_win->img_position_offset =
			(t_xyz_values *)ft_memalloc(sizeof(*mlx_win->img_position_offset));
	mlx_win->img_size.x = 5000;
	mlx_win->img_size.y = 5000;
	mlx_win->img_start_position =
				(t_position *)ft_memalloc(sizeof(*mlx_win->img_start_position));
	mlx_win->render_action = e_no_action;
	mlx_win->img_line_lst =
					(t_list **)ft_memalloc(sizeof(*mlx_win->img_line_lst));
	mlx_win->object_type_lst =
					(t_list **)ft_memalloc(sizeof(*mlx_win->object_type_lst));
	create_object_types(mlx_win->object_type_lst, input->map, input);
	mlx_win->angle = input->angle;
	ft_log_info("Start angle: x=%.0f, y=%.0f z=%.0f\n", mlx_win->angle->x,
										mlx_win->angle->y, mlx_win->angle->z);
	mlx_win->angle_step = input->cmd_args->angle_steps;
	elem_altitude = input->map->elem_altitude;
	mlx_win->element_map_size = input->map->map_size;
	i = -1;
	while (++i < input->map->map_size->y)
	{
		j = -1;
		while (++j < input->map->map_size->x)
			ft_log_trace(" %3d", elem_altitude[i][j]);
	}
	mlx_win->mlx = mlx_init();
	initialize_window(mlx_win, "Minilibx training 4 (ex4)");
	mlx_win->empty_img = mlx_new_image(mlx_win->mlx, mlx_win->img_size.x,
														mlx_win->img_size.y);
	mlx_win->img = mlx_new_image(mlx_win->mlx, mlx_win->img_size.x,
														mlx_win->img_size.y);
	mlx_win->elem_table =
						(t_element ***)ft_memalloc(sizeof(*mlx_win->elem_table)
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
	rotate_objects(mlx_win->object_type_lst, input->angle);
	create_elements(input->map, mlx_win->elem_table, mlx_win);
	i = -1;
	while (++i < input->map->map_size->y)
	{
		j = -1;
		while (++j < input->map->map_size->x)
		{
			mlx_win->elem_table[i][j]->elem_position_offset.x =
								(int)(mlx_win->img_position_offset->x +
							mlx_win->elem_table[i][j]->start_position->x + 0.5);
			mlx_win->elem_table[i][j]->elem_position_offset.y =
								(int)(mlx_win->img_position_offset->y +
							mlx_win->elem_table[i][j]->start_position->y + 0.5);
			// draw_lines(mlx_win->img, mlx_win->elem_table[i][j]);
		}
	}
	draw_img_lines(mlx_win->img_line_lst, mlx_win->img);
	mlx_win->render_action = e_put_image_to_window;
	mlx_loop_hook(mlx_win->mlx, render_frame, mlx_win);
	mlx_loop(mlx_win->mlx);
	release_mlx_win(&mlx_win);
	release_input_data(&input);
	return (0);
}
