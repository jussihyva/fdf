/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 15:53:14 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/21 19:55:14 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		draw_line(t_win_ptr *p)
{
	int		color;
	int		x;
	int		y;

	color = 0 << 16;
	color += 250 << 8;
	color += 0;
	x = 10;
	y = 10;
	while (++x < 30)
		mlx_pixel_put(p->mlx_ptr, p->win_ptr, x, y, color);
	return ;
}
