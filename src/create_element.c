/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_element.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 03:44:46 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/22 19:33:46 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			set_elem_line(t_elem_line *elem_line, t_xyz_values *start,
										t_xyz_values *end, t_element *element)
{
	elem_line->start = start;
	elem_line->end = end;
	elem_line->line_type = 0;
	elem_line->start_elem = element;
	elem_line->end_elem = element;
	elem_line->color = element->color;
	return ;
}

static t_elem_line	*set_elem_lines(t_element *element)
{
	t_xyz_values	*positions;
	t_elem_line		*elem_lines;
	int				num_of_lines;

	positions = element->object_type->current_positions;
	num_of_lines = 12;
	elem_lines = (t_elem_line *)ft_memalloc(sizeof(*elem_lines) * num_of_lines);
	set_elem_line(&elem_lines[0], &positions[0], &positions[1], element);
	set_elem_line(&elem_lines[1], &positions[0], &positions[2], element);
	set_elem_line(&elem_lines[2], &positions[0], &positions[4], element);
	set_elem_line(&elem_lines[3], &positions[1], &positions[3], element);
	set_elem_line(&elem_lines[4], &positions[1], &positions[5], element);
	set_elem_line(&elem_lines[5], &positions[2], &positions[3], element);
	set_elem_line(&elem_lines[6], &positions[2], &positions[6], element);
	set_elem_line(&elem_lines[7], &positions[3], &positions[7], element);
	set_elem_line(&elem_lines[8], &positions[4], &positions[5], element);
	set_elem_line(&elem_lines[9], &positions[4], &positions[6], element);
	set_elem_line(&elem_lines[10], &positions[5], &positions[7], element);
	set_elem_line(&elem_lines[11], &positions[6], &positions[7], element);
	return (elem_lines);
}

static t_element	*create_element(t_mlx_win *mlx_win, int color,
					t_xyz_values *start_position, t_object_type *object_type)
{
	t_element		*element;
	t_xyz_values	*img_position_offset;

	img_position_offset = mlx_win->img_position_offset;
	element = (t_element *)ft_memalloc(sizeof(*element));
	element->color = color;
	element->angle = (t_xyz_values *)ft_memalloc(sizeof(*element->angle));
	element->object_type = object_type;
	element->start_position =
				(t_xyz_values *)ft_memalloc(sizeof(*element->start_position));
	ft_memcpy(element->angle, mlx_win->angle, sizeof(*element->angle));
	get_max_position_offset(element->object_type->current_positions,
										img_position_offset, start_position);
	element->elem_lines = set_elem_lines(element);
	ft_memcpy(element->start_position, start_position,
											sizeof(*element->start_position));
	return (element);
}

void				set_next_start_position(t_xyz_values *elem_start_position,
							t_element *element, t_xyz_values *current_position)
{
	t_xyz_values	*start_position;

	start_position = element->start_position;
	elem_start_position->x = start_position->x + current_position->x;
	elem_start_position->y = start_position->y + current_position->y;
	return ;
}

void				create_elements(t_map *map, t_element ***elem_table,
															t_mlx_win *mlx_win)
{
	int				i;
	int				j;
	t_xyz_values	next_start_position;
	t_object_type	*object_type;
	int				color;

	set_position(&next_start_position, 0, 0, 0);
	i = -1;
	while (++i < map->map_size->y)
	{
		j = -1;
		while (++j < map->map_size->x)
		{
			object_type = map->object_type[i][j];
			color = get_element_color(map, object_type, map->elem_color[i][j]);
			elem_table[i][j] = create_element(mlx_win, color,
											&next_start_position, object_type);
			add_image_lines(mlx_win->img_line_lst, elem_table, i, j);
			set_next_start_position(&next_start_position, elem_table[i][j],
											&object_type->current_positions[1]);
		}
		object_type = map->object_type[i][0];
		set_next_start_position(&next_start_position, elem_table[i][0],
											&object_type->current_positions[2]);
	}
}
