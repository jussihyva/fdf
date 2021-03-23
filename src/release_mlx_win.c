/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_mlx_win.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 19:41:05 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/23 09:18:50 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		release_rotation_matrix(double ***rotation_matrix,
														int *is_rotation_matrix)
{
	size_t		i;
	size_t		j;

	i = -1;
	while (++i < 360)
	{
		if (is_rotation_matrix[i])
		{
			j = -1;
			while (++j < 3)
				ft_memdel((void **)&rotation_matrix[i][j]);
			ft_memdel((void **)&rotation_matrix[i]);
		}
	}
	return ;
}

static void		delete_object_type(void *content, size_t size)
{
	t_object_type	*object_type;

	(void)size;
	object_type = *(t_object_type **)content;
	ft_memdel((void **)&object_type->start_positions);
	ft_memdel((void **)&object_type->current_positions);
	ft_memdel((void **)&object_type);
	ft_memdel(&content);
	return ;
}

static void		delete_img_line(void *content, size_t size)
{
	t_elem_line	*elem_line;

	(void)size;
	elem_line = *(t_elem_line **)content;
	ft_memdel((void **)&elem_line);
	ft_memdel(&content);
	return ;
}

void			release_mlx_win(t_mlx_win **mlx_win)
{
	mlx_destroy_image((*mlx_win)->mlx, (*mlx_win)->empty_img);
	mlx_destroy_image((*mlx_win)->mlx, (*mlx_win)->img);
	release_elements((*mlx_win)->element_map_size, (*mlx_win)->elem_table);
	ft_memdel((void **)&(*mlx_win)->elem_table);
	mlx_destroy_window((*mlx_win)->mlx, (*mlx_win)->win);
	mlx_destroy_display((*mlx_win)->mlx);
	ft_memdel((void **)&(*mlx_win)->mlx);
	ft_memdel((void **)&(*mlx_win)->img_start_position);
	ft_memdel((void **)&(*mlx_win)->img_position_offset);
	ft_memdel((void **)&(*mlx_win)->first_elem_start_position);
	ft_lstdel((*mlx_win)->object_type_lst, delete_object_type);
	ft_memdel((void **)&(*mlx_win)->object_type_lst);
	ft_lstdel((*mlx_win)->img_line_lst, delete_img_line);
	ft_memdel((void **)&(*mlx_win)->img_line_lst);
	release_rotation_matrix((*mlx_win)->z_rotation_matrix,
											(*mlx_win)->z_is_rotation_matrix);
	release_rotation_matrix((*mlx_win)->y_rotation_matrix,
											(*mlx_win)->y_is_rotation_matrix);
	release_rotation_matrix((*mlx_win)->x_rotation_matrix,
											(*mlx_win)->x_is_rotation_matrix);
	ft_memdel((void **)mlx_win);
	return ;
}
