/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:32:32 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/27 17:11:09 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		free_memory(t_fdf_data *fdf_data)
{
	free(fdf_data->line_img_data);
	free(fdf_data->input);
	free(fdf_data);
	return ;
}

static void		activate_mlx_events(t_fdf_data *fdf_data)
{
	mlx_mouse_hook(fdf_data->win_ptr, &mouse_key_event, fdf_data);
	mlx_hook(fdf_data->win_ptr, 6, 0, &mouse_wheel_event, fdf_data);
	return ;
}

static void		move_line_with_mouse(t_fdf_data *fdf_data)
{
	fdf_data->line_img_data = create_line_image(fdf_data->window,
															fdf_data->mlx_ptr);
	activate_mlx_events(fdf_data);
	return ;
}

int				main(int argc, char **argv)
{
	t_fdf_data			*fdf_data;
	t_mlx_image_data	*img_data;

	fdf_data = (t_fdf_data *)ft_memalloc(sizeof(*fdf_data));
	fdf_data->input = read_command_attributes(argc, argv);
	fdf_data->mlx_ptr = mlx_init();
	fdf_data->window.width = fdf_data->input->width;
	fdf_data->window.hight = fdf_data->input->hight;
	img_data = create_empty_image(fdf_data->window, fdf_data->mlx_ptr);
	read_map_file(fdf_data->input, img_data);
	ft_printf("Lines in the file (%s): %d\n", fdf_data->input->input_file_path,
											fdf_data->input->input_array_size);
	fdf_data->win_ptr = mlx_new_window(fdf_data->mlx_ptr,
						fdf_data->window.width, fdf_data->window.hight, "FdF!");
	if (fdf_data->input->opt & e_test)
		move_line_with_mouse(fdf_data);
	else
		mlx_put_image_to_window(fdf_data->mlx_ptr, fdf_data->win_ptr,
													img_data->img_ptr, 0, 0);
	mlx_key_hook(fdf_data->win_ptr, &keyboard_event, fdf_data);
	mlx_hook(fdf_data->win_ptr, 17, 0, &close_window_event, fdf_data);
	mlx_loop(fdf_data->mlx_ptr);
	free_memory(fdf_data);
	return (0);
}
