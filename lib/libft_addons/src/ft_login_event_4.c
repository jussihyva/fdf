/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_login_event_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 08:22:12 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/23 08:26:25 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static void			format_time_stamp(struct timeval tv, char *time_string,
											size_t size, char *format_string)
{
	int			millisec;
	struct tm	*tm_info;

	millisec = lrint(tv.tv_usec / 1000.0);
	if (millisec >= 1000)
	{
		millisec -= 1000;
		tv.tv_sec++;
	}
	tm_info = localtime(&tv.tv_sec);
	strftime(time_string, size, format_string, tm_info);
	ft_sprintf(time_string + ft_strlen(format_string), ".%03d", millisec);
	return ;
}

void				stdout_callback(t_log_event *event)
{
	char		buf[16];

	format_time_stamp(event->tv, buf, sizeof(buf), "%H:%M:%S");
	ft_dprintf(
		event->fd, "%s %s%-5s\x1b[0m \x1b[90m%s:%d:\x1b[0m ",
								buf, g_loging_params.level_colors[event->level],
									g_loging_params.level_strings[event->level],
													event->file, event->line);
	ft_vdprintf(event->fd, event->fmt, event->ap);
	ft_dprintf(event->fd, "\n");
}

void				file_callback(t_log_event *event)
{
	char		buf[64];

	format_time_stamp(event->tv, buf, sizeof(buf), "%Y-%m-%d %H:%M:%S");
	ft_dprintf(event->fd, "%s %-5s %s:%d: ", buf,
									g_loging_params.level_strings[event->level],
													event->file, event->line);
	ft_vdprintf(event->fd, event->fmt, event->ap);
	ft_dprintf(event->fd, "\n");
}

void				lock(void)
{
	if (g_loging_params.lock)
	{
		g_loging_params.lock(1, g_loging_params.udata);
	}
}

void				unlock(void)
{
	if (g_loging_params.lock)
	{
		g_loging_params.lock(1, g_loging_params.udata);
	}
}
