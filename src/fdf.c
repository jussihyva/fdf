/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:32:32 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/23 12:30:45 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			main(int argc, char **argv)
{
	t_input			*input;
	t_fdf_data		fdf_data;
	int				width;
	int				hight;
	void			*line_img;

	input = (t_input *)ft_memalloc(sizeof(*input));
	ft_step_args(&argc, &argv);
	read_opt(input, &argc, &argv);
	width = 900;
	hight = 600;
	fdf_data.mlx_ptr = mlx_init();
	fdf_data.win_ptr = mlx_new_window(fdf_data.mlx_ptr, width, hight, "FdF!");
	mlx_key_hook(fdf_data.win_ptr, &keyboard_event, &fdf_data);
	mlx_mouse_hook(fdf_data.win_ptr, &mouse_key_event, &fdf_data);
	mlx_hook(fdf_data.win_ptr, 6, 0, &mouse_wheel_event, &fdf_data);
	mlx_hook(fdf_data.win_ptr, 17, 0, &close_window_event, &fdf_data);
	line_img = create_line_image(fdf_data.mlx_ptr);
	mlx_put_image_to_window(fdf_data.mlx_ptr, fdf_data.win_ptr, line_img, 0, 0);
	if (input->opt & leaks)
		system("leaks fdf");
	mlx_loop(fdf_data.mlx_ptr);
	free(input);
	return (0);
}
