/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_mlx_win.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 19:41:05 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/21 01:12:01 by jkauppi          ###   ########.fr       */
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

static void		release_element(t_element **element)
{
	if (*element)
	{
		ft_memdel((void **)&(*element)->start_position);
		ft_memdel((void **)&(*element)->elem_lines);
		ft_memdel((void **)&(*element)->angle);
		ft_memdel((void **)element);
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

static void		release_elements(t_xy_values_old *element_map_size,
														t_element ***elem_table)
{
	int			i;
	int			j;

	i = -1;
	while (++i < element_map_size->y)
	{
		j = -1;
		while (++j < element_map_size->x)
			release_element(&elem_table[i][j]);
		ft_memdel((void **)&elem_table[i]);
	}
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
	ft_memdel((void **)mlx_win);
	release_rotation_matrix(g_z_rotation_matrix, g_z_is_rotation_matrix);
	release_rotation_matrix(g_y_rotation_matrix, g_y_is_rotation_matrix);
	release_rotation_matrix(g_x_rotation_matrix, g_x_is_rotation_matrix);
	return ;
}

void			release_input_data(t_input **input)
{
	int			i;

	i = -1;
	if ((*input)->map)
	{
		while (++i < (*input)->map->map_size->y)
		{
			ft_memdel((void **)&(*input)->map->object_type[i]);
			ft_memdel((void **)&(*input)->map->elem_altitude[i]);
			ft_memdel((void **)&(*input)->map->elem_color[i]);
		}
		ft_memdel((void **)&(*input)->map->object_type);
		ft_memdel((void **)&(*input)->map->elem_altitude);
		ft_memdel((void **)&(*input)->map->elem_color);
		ft_memdel((void **)&(*input)->map->map_size);
		ft_memdel((void **)&(*input)->map);
	}
	ft_memdel((void **)&(*input)->cmd_args);
	ft_memdel((void **)&(*input)->angle);
	ft_memdel((void **)&(*input)->level_strings);
	ft_memdel((void **)&(*input)->level_colors);
	ft_memdel((void **)input);
	return ;
}
