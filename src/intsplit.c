/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intsplit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 17:55:33 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/25 19:57:18 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void		save_word(int *array, char *s, int w_count)
{
	char	*endptr;

	endptr = NULL;
	array[w_count] = ft_strtoi(s, &endptr, 10);
	return ;
}

static int		count_save(char *s, char c, int *array)
{
	int		w_count;
	int		w_len;

	w_count = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			w_len = 0;
			while (*s && *s != c)
			{
				w_len++;
				s++;
			}
			if (array)
				save_word(array, s, w_count);
			w_count += 1;
		}
	}
	if (array)
		*(array + w_count) = 0;
	return (w_count);
}

int				*intsplit(char const *s, char c, int *num_of_words)
{
	int			*array;

	array = 0;
	*num_of_words = count_save((char *)s, c, array);
	array = (int *)malloc(sizeof(*array) * *num_of_words);
	*num_of_words = count_save((char *)s, c, array);
	return (array);
}
