/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:32:32 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/27 11:20:28 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		activate_mlx_events(t_fdf_data *fdf_data)
{
	mlx_key_hook(fdf_data->win_ptr, &keyboard_event, fdf_data);
	mlx_mouse_hook(fdf_data->win_ptr, &mouse_key_event, fdf_data);
	mlx_hook(fdf_data->win_ptr, 6, 0, &mouse_wheel_event, fdf_data);
	mlx_hook(fdf_data->win_ptr, 17, 0, &close_window_event, fdf_data);
	return ;
}

static void		move_line_with_mouse(t_fdf_data *fdf_data)
{
	fdf_data->win_ptr = mlx_new_window(fdf_data->mlx_ptr,
						fdf_data->window.width, fdf_data->window.hight, "FdF!");
	fdf_data->line_img_data = create_line_image(fdf_data->window.width,
									fdf_data->window.hight, fdf_data->mlx_ptr);
	return ;
}

int				main(int argc, char **argv)
{
	t_fdf_data		*fdf_data;
	void			*img_data;
	t_window		window;

	fdf_data = (t_fdf_data *)ft_memalloc(sizeof(*fdf_data));
	fdf_data->mlx_ptr = mlx_init();
	window.width = 900;
	window.hight = 600;
	img_data = create_empty_image(window.width, window.hight,
															fdf_data->mlx_ptr);
	fdf_data->input = read_command_attributes(argc, argv);
	read_map_file(fdf_data->input, img_data);
	ft_printf("Lines in the file (%s): %d\n", fdf_data->input->input_file_path,
											fdf_data->input->input_array_size);
	fdf_data->window = window;
	move_line_with_mouse(fdf_data);
	activate_mlx_events(fdf_data);
	mlx_loop(fdf_data->mlx_ptr);
	free(fdf_data->line_img_data);
	free(fdf_data->input);
	free(fdf_data);
	return (0);
}
