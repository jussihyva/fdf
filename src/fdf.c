/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:32:32 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/25 13:18:05 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			main(int argc, char **argv)
{
	t_fdf_data		*fdf_data;

	fdf_data = (t_fdf_data *)ft_memalloc(sizeof(*fdf_data));
	fdf_data->input = (t_input *)ft_memalloc(sizeof(*fdf_data->input));
	ft_step_args(&argc, &argv);
	read_opt(fdf_data->input, &argc, &argv);
	fdf_data->window.width = 900;
	fdf_data->window.hight = 600;
	fdf_data->mlx_ptr = mlx_init();
	fdf_data->win_ptr = mlx_new_window(fdf_data->mlx_ptr,
						fdf_data->window.width, fdf_data->window.hight, "FdF!");
	fdf_data->line_img_data = create_line_image(fdf_data->window.width,
									fdf_data->window.hight, fdf_data->mlx_ptr);
	mlx_key_hook(fdf_data->win_ptr, &keyboard_event, fdf_data);
	mlx_mouse_hook(fdf_data->win_ptr, &mouse_key_event, fdf_data);
	mlx_hook(fdf_data->win_ptr, 6, 0, &mouse_wheel_event, fdf_data);
	mlx_hook(fdf_data->win_ptr, 17, 0, &close_window_event, fdf_data);
	mlx_loop(fdf_data->mlx_ptr);
	free(fdf_data->line_img_data);
	free(fdf_data->input);
	free(fdf_data);
	return (0);
}
