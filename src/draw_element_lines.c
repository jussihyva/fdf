/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_element_lines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 23:12:39 by juhani            #+#    #+#             */
/*   Updated: 2021/03/22 11:30:41 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			draw_lines(t_mlx_win *mlx_win, t_element *element)
{
	t_elem_line		*elem_lines;
	t_elem_line		elem_line;
	int				i;

	elem_lines = (t_elem_line *)element->elem_lines;
	i = -1;
	ft_log_trace("Draw element lines %s %3.2f,%3.2f", "(start position):",
					element->start_position->x, element->start_position->y);
	while (++i < 12)
	{
		elem_line = elem_lines[i];
		bresenham_draw_line(mlx_win, &elem_line);
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
