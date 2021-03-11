/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_addons.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:53:13 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/10 01:22:28 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_ADDONS_H
# define LIBFT_ADDONS_H
# include <sys/types.h>

# define PI							3.141592654

typedef struct	s_matrix_size
{
	size_t		rows;
	size_t		columns;
}				t_matrix_size;

double			ft_radian(double angle_degree);
int				ft_max_int(int nbr1, int nbr2);
int				ft_min_int(int nbr1, int nbr2);
double 			ft_mod_double(double dividend, double divisor);
int 			ft_mod_int(int dividend, int divisor);
void			ft_matrix_x_vector_double(t_matrix_size matrix_size,
						double **matrix, double *vector, double *new_vector);

#endif
