/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_login_event_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 08:22:06 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/23 08:28:48 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

void				ft_log_set_lock(t_loging_lock_function fn, void *udata)
{
	g_loging_params.lock = fn;
	g_loging_params.udata = udata;
}

void				ft_log_set_level(int level)
{
	g_loging_params.level = level;
}

void				ft_log_set_quiet(int enable)
{
	g_loging_params.quiet = enable;
}

static int			log_add_callback(t_loging_function fn, int fd, int level)
{
	t_loging_extension		*loging_extension;
	size_t					i;

	loging_extension =
				(t_loging_extension *)ft_memalloc(sizeof(*loging_extension));
	loging_extension->fn = fn;
	loging_extension->fd = fd;
	loging_extension->level = level;
	i = -1;
	while (++i < MAX_LOGING_EXTENSIONS)
	{
		if (!g_loging_params.loging_extensions[i])
		{
			g_loging_params.loging_extensions[i] = loging_extension;
			return (0);
		}
	}
	return (-1);
}

int					ft_log_add_fp(int fd, int level)
{
	return (log_add_callback(file_callback, fd, level));
}
