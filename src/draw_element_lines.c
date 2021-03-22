/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_element_lines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 23:12:39 by juhani            #+#    #+#             */
/*   Updated: 2021/03/22 18:20:20 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			draw_lines(t_mlx_win *mlx_win)
{
	t_elem_line		*elem_lines;
	int				i;
	int				j;
	int				k;
	t_element		*element;

	i = -1;
	while (++i < mlx_win->element_map_size->y)
	{
		j = -1;
		while (++j < mlx_win->element_map_size->x)
		{
			element = mlx_win->elem_table[i][j];
			elem_lines = (t_elem_line *)element->elem_lines;
			ft_log_trace("Draw element lines %s %3.2f,%3.2f",
															"(start position):",
						element->start_position->x, element->start_position->y);
			k = -1;
			while (++k < 12)
				bresenham_draw_line(mlx_win, &elem_lines[k]);
		}
	}
	return ;
}

void			draw_img_lines(t_mlx_win *mlx_win)
{
	t_list			*elem;
	t_elem_line		*elem_line;

	elem = *mlx_win->img_line_lst;
	while (elem)
	{
		elem_line = *((t_elem_line **)elem->content);
		bresenham_draw_line(mlx_win, elem_line);
		elem = elem->next;
	}
	return ;
}
