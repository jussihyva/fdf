/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_functions1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 12:47:12 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/22 19:27:18 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		change_angle(int keycode, t_xyz_values *angle,
															double angle_step)
{
	if (keycode == 'a')
		angle->x = (double)((int)(angle->x + angle_step) % 360);
	else if (keycode == 'z')
		angle->x = (angle->x >= angle_step) ?
								(double)((int)(angle->x - angle_step) % 360) :
												(angle->x + 360 - angle_step);
	else if (keycode == 's')
		angle->y = (double)((int)(angle->y + angle_step) % 360);
	else if (keycode == 'x')
		angle->y = (angle->y >= angle_step) ?
								(double)((int)(angle->y - angle_step) % 360) :
												(angle->y + 360 - angle_step);
	else if (keycode == 'd')
		angle->z = (double)((int)(angle->z + angle_step) % 360);
	else if (keycode == 'c')
		angle->z = (angle->z >= angle_step) ?
								(double)((int)(angle->z - angle_step) % 360) :
												(angle->z + 360 - angle_step);
	ft_log_info("Image angle: x=%03.0f y=%03.0f z=%03.0f", angle->x, angle->y,
																	angle->z);
	return ;
}

static void		update_elem_position(t_xyz_values *next_start_position,
										t_mlx_win *mlx_win, t_element *element)
{
	t_object_type	*object_type;

	object_type = element->object_type;
	ft_memcpy(element->start_position, next_start_position,
									sizeof(*element->start_position));
	get_max_position_offset(object_type->current_positions,
				mlx_win->img_position_offset, element->start_position);
	set_next_start_position(next_start_position, element,
											&object_type->current_positions[1]);
	return ;
}

static void		update_elem_positions(t_mlx_win *mlx_win)
{
	t_xyz_values	next_start_position;
	t_object_type	*object_type;
	int				i;
	int				j;

	ft_bzero(mlx_win->img->data, mlx_win->img_size.y * mlx_win->img->size_line /
						4 + mlx_win->img_size.x * (mlx_win->img->bpp / 8));
	ft_bzero(mlx_win->img_position_offset,
										sizeof(*mlx_win->img_position_offset));
	ft_memcpy(&next_start_position, mlx_win->elem_table[0][0]->start_position,
												sizeof(next_start_position));
	i = -1;
	while (++i < mlx_win->element_map_size->y)
	{
		j = -1;
		while (++j < mlx_win->element_map_size->x)
			update_elem_position(&next_start_position, mlx_win,
													mlx_win->elem_table[i][j]);
		object_type = mlx_win->elem_table[i][0]->object_type;
		set_next_start_position(&next_start_position, mlx_win->elem_table[i][0],
											&object_type->current_positions[2]);
	}
	return ;
}

int				button_press(int keycode, int x, int y, t_mlx_win *mlx_win)
{
	(void)mlx_win;
	ft_printf("Key: %d, Mouse location: x:%d, y:%d\n", keycode, x, y);
	return (0);
}

int				key_press(int keycode, t_mlx_win *mlx_win)
{
	if (keycode == 65307)
		close_win(mlx_win);
	else if (mlx_win->render_action != e_no_action)
		;
	else if (ft_strchr("asdzxc", keycode))
	{
		change_angle(keycode, mlx_win->angle, mlx_win->angle_step);
		rotate_objects(mlx_win->object_type_lst, mlx_win->angle);
		update_elem_positions(mlx_win);
		if (mlx_win->drawing_mode == 2)
			draw_lines(mlx_win);
		else
			draw_img_lines(mlx_win);
		mlx_win->render_action = e_put_image_to_window;
	}
	else
		ft_log_info("keycode: %#x\n", keycode);
	return (0);
}
