/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_functions1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 12:47:12 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/11 13:07:04 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		change_angle(int keycode, t_position *angle, int angle_step)
{
	if (keycode == 'a')
		angle->x = (angle->x + angle_step) % 360;
	else if (keycode == 'z')
		angle->x = (angle->x >= angle_step) ? (angle->x - angle_step) % 360 :
												(angle->x + 360 - angle_step);
	else if (keycode == 's')
		angle->y = (angle->y + angle_step) % 360;
	else if (keycode == 'x')
		angle->y = (angle->y >= angle_step) ? (angle->y - angle_step) % 360 :
												(angle->y + 360 - angle_step);
	else if (keycode == 'd')
		angle->z = (angle->z + angle_step) % 360;
	else if (keycode == 'c')
		angle->z = (angle->z >= angle_step) ? (angle->z - angle_step) % 360 :
												(angle->z + 360 - angle_step);
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
	t_position		*position_offset;
	t_position		elem_start_position;
	int				i;
	int				j;

	position_offset = (t_position *)ft_memalloc(sizeof(*position_offset));
	if (keycode == 65307)
		close_win(mlx_win);
	else if (mlx_win->render_action != e_no_action)
		;
	else if (ft_strchr("asdzxc", keycode))
	{
		change_angle(keycode, mlx_win->angle, mlx_win->angle_step);
		ft_bzero(mlx_win->img->data, mlx_win->img_size.y * mlx_win->img->size_line / 4 +
										mlx_win->img_size.x * (mlx_win->img->bpp / 8));
		ft_memcpy(&elem_start_position, mlx_win->elem_table[0][0]->start_position, sizeof(elem_start_position));
		i = -1;
		while (++i < mlx_win->element_map_size->y)
		{
			j = -1;
			while (++j < mlx_win->element_map_size->x)
			{
				ft_memcpy(mlx_win->elem_table[i][j]->start_position,
														&elem_start_position,
								sizeof(mlx_win->elem_table[i][j]->start_position));
				elemental_rotation(mlx_win->elem_table[i][j], mlx_win->angle,
								position_offset, mlx_win->elem_table[i][j]->start_position);
				ft_memcpy(&elem_start_position, mlx_win->elem_table[i][j]->start_position, sizeof(elem_start_position));
				elem_start_position.x += mlx_win->elem_table[i][j]->current_positions[1].x;
				elem_start_position.y += mlx_win->elem_table[i][j]->current_positions[1].y;
			}
			ft_memcpy(&elem_start_position, &mlx_win->elem_table[i][0]->current_positions[2], sizeof(elem_start_position));
			elem_start_position.x *= (i + 1);
			elem_start_position.y *= (i + 1);
		}
		ft_log_info("Image angle: x=%d, y=%d z=%d", mlx_win->angle->x, mlx_win->angle->y, mlx_win->angle->z);
		i = -1;
		while (++i < mlx_win->element_map_size->y)
		{
			j = -1;
			while (++j < mlx_win->element_map_size->x)
			{
				mlx_win->elem_table[i][j]->elem_position_offset.x = position_offset->x + mlx_win->elem_table[i][j]->start_position->x;
				mlx_win->elem_table[i][j]->elem_position_offset.y = position_offset->y + mlx_win->elem_table[i][j]->start_position->y;
				draw_lines(mlx_win->img, mlx_win->elem_table[i][j]);
			}
		}
		mlx_win->render_action = e_put_image_to_window;
	}
	else
		ft_printf("keycode: %#x\n", keycode);
	ft_memdel((void **)&position_offset);
	return (0);
}
