/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_functions_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:25:34 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/22 16:26:00 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	d_one(double nbr)
{
	(void)nbr;
	return ((double)1);
}

double	d_zero(double nbr)
{
	(void)nbr;
	return ((double)0);
}

double	neg_sin(double nbr)
{
	return (-sin(nbr));
}
