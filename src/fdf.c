/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:32:32 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/22 17:32:49 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			main(void)
{
	t_fdf_data		fdf_data;
	int				width;
	int				hight;
	void			*line_img;

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
	mlx_loop(fdf_data.mlx_ptr);
	return (0);
}
