/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:32:32 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/23 13:28:45 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			main(int argc, char **argv)
{
	t_input			*input;
	t_fdf_data		*fdf_data;

	input = (t_input *)ft_memalloc(sizeof(*input));
	fdf_data = (t_fdf_data *)ft_memalloc(sizeof(*fdf_data));
	ft_step_args(&argc, &argv);
	read_opt(input, &argc, &argv);
	fdf_data->window.width = 900;
	fdf_data->window.hight = 600;
	fdf_data->mlx_ptr = mlx_init();
	fdf_data->win_ptr = mlx_new_window(fdf_data->mlx_ptr,
						fdf_data->window.width, fdf_data->window.hight, "FdF!");
	mlx_key_hook(fdf_data->win_ptr, &keyboard_event, fdf_data);
	mlx_mouse_hook(fdf_data->win_ptr, &mouse_key_event, fdf_data);
	mlx_hook(fdf_data->win_ptr, 6, 0, &mouse_wheel_event, fdf_data);
	mlx_hook(fdf_data->win_ptr, 17, 0, &close_window_event, fdf_data);
	if (input->opt & leaks)
		system("leaks fdf");
	mlx_loop(fdf_data->mlx_ptr);
	free(input);
	free(fdf_data);
	return (0);
}
