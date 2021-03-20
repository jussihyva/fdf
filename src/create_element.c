/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_element.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 03:44:46 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/21 00:59:41 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			set_elem_line(t_elem_line *elem_line, t_xyz_values *start,
															t_xyz_values *end)
{
	elem_line->start = start;
	elem_line->end = end;
	elem_line->line_type = 0;
	return ;
}

static t_elem_line	*set_elem_lines(t_xyz_values *elem_positions)
{
	t_elem_line		*elem_lines;
	int				num_of_lines;

	num_of_lines = 12;
	elem_lines = (t_elem_line *)ft_memalloc(sizeof(*elem_lines) *
																num_of_lines);
	set_elem_line(&elem_lines[0], &elem_positions[0], &elem_positions[1]);
	set_elem_line(&elem_lines[1], &elem_positions[0], &elem_positions[2]);
	set_elem_line(&elem_lines[2], &elem_positions[0], &elem_positions[4]);
	set_elem_line(&elem_lines[3], &elem_positions[1], &elem_positions[3]);
	set_elem_line(&elem_lines[4], &elem_positions[1], &elem_positions[5]);
	set_elem_line(&elem_lines[5], &elem_positions[2], &elem_positions[3]);
	set_elem_line(&elem_lines[6], &elem_positions[2], &elem_positions[6]);
	set_elem_line(&elem_lines[7], &elem_positions[3], &elem_positions[7]);
	set_elem_line(&elem_lines[8], &elem_positions[4], &elem_positions[5]);
	set_elem_line(&elem_lines[9], &elem_positions[4], &elem_positions[6]);
	set_elem_line(&elem_lines[10], &elem_positions[5], &elem_positions[7]);
	set_elem_line(&elem_lines[11], &elem_positions[6], &elem_positions[7]);
	return (elem_lines);
}

t_element			*create_element(t_mlx_win *mlx_win,
					t_xyz_values *start_position, t_xyz_values *position_offset,
						t_object_type *object_type)
{
	t_element	*element;

	element = (t_element *)ft_memalloc(sizeof(*element));
	element->angle = (t_xyz_values *)ft_memalloc(sizeof(*element->angle));
	element->object_type = object_type;
	element->start_position =
				(t_xyz_values *)ft_memalloc(sizeof(*element->start_position));
	ft_memcpy(element->angle, mlx_win->angle, sizeof(*element->angle));
	elemental_rotation(element->object_type->current_positions,
				&element->object_type->angle, position_offset, start_position);
	element->elem_lines =
						set_elem_lines(element->object_type->current_positions);
	ft_memcpy(element->start_position, start_position,
											sizeof(*element->start_position));
	return (element);
}

static void			set_next_start_position(t_xyz_values *elem_start_position,
							t_element *element, t_xyz_values *current_position)
{
	t_xyz_values	*start_position;

	start_position = element->start_position;
	elem_start_position->x = start_position->x + current_position->x;
	elem_start_position->y = start_position->y + current_position->y;
	return ;
}

static void			add_image_lines(t_list **img_line_lst,
										t_element ***elem_table, int i, int j)
{
	t_elem_line		*elem_line;
	t_list			*elem;

	if (i)
	{
		elem_line = (t_elem_line *)ft_memalloc(sizeof(*elem_line));
		elem_line->color = 0x00FF00;
		elem_line->start = &elem_table[i][j]->object_type->start_positions[4];
		elem_line->end = &elem_table[i - 1][j]->object_type->start_positions[4];
		elem = ft_lstnew(&elem_line, sizeof(elem_line));
		ft_lstadd(img_line_lst, elem);
	}
	if (j)
	{
		elem_line = (t_elem_line *)ft_memalloc(sizeof(*elem_line));
		elem_line->color = 0x00FF00;
		elem_line->start = &elem_table[i][j]->object_type->start_positions[4];
		elem_line->end = &elem_table[i][j - 1]->object_type->start_positions[4];
		elem = ft_lstnew(&elem_line, sizeof(elem_line));
		ft_lstadd(img_line_lst, elem);
	}
	return ;
}

void				create_elements(t_map *map, t_element ***elem_table,
															t_mlx_win *mlx_win)
{
	int				i;
	int				j;
	t_xyz_values	next_start_position;
	t_object_type	*object_type;

	set_position(&next_start_position, 0, 0, 0);
	i = -1;
	while (++i < map->map_size->y)
	{
		j = -1;
		while (++j < map->map_size->x)
		{
			object_type = map->object_type[i][j];
			elem_table[i][j] = create_element(mlx_win, &next_start_position,
									mlx_win->img_position_offset, object_type);
			set_element_color(map, elem_table[i][j], map->elem_color[i][j]);
			add_image_lines(mlx_win->img_line_lst, elem_table, i, j);
			set_next_start_position(&next_start_position, elem_table[i][j],
											&object_type->current_positions[1]);
		}
		object_type = map->object_type[i][0];
		set_next_start_position(&next_start_position, elem_table[i][0],
											&object_type->current_positions[2]);
	}
	return ;
}
