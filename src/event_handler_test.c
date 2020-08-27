/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 17:12:36 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/27 17:13:31 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_event_order	validate_test_orders(int key, t_fdf_data *fdf_data)
{
	t_event_order	event_order;

	event_order = e_update_line_img;
	if (key == 123 && fdf_data->line_img_data->line.end_pos.x)
		fdf_data->line_img_data->line.end_pos.x--;
	else if (key == 124 && fdf_data->line_img_data->line.end_pos.x <
													fdf_data->window.width - 1)
		fdf_data->line_img_data->line.end_pos.x++;
	else if (key == 126 && fdf_data->line_img_data->line.end_pos.y)
		fdf_data->line_img_data->line.end_pos.y--;
	else if (key == 125 && fdf_data->line_img_data->line.end_pos.y <
													fdf_data->window.hight - 1)
		fdf_data->line_img_data->line.end_pos.y++;
	return (event_order);
}
