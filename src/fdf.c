/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:32:32 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/21 14:10:18 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			main(void)
{
	void	*mlx1_ptr;
	void	*win1_ptr;
	int		win1_width;
	int		win1_length;

	win1_width = 1000;
	win1_length = 1000;
	mlx1_ptr = mlx_init();
	win1_ptr = mlx_new_window(mlx1_ptr, win1_width, win1_length, "MOI!");
	mlx_loop(win1_ptr);
	return (0);
}
