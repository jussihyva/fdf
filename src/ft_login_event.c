/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_login_event.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 10:22:34 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/21 00:36:03 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_loging_params		g_loging_params;

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

static void			stdout_callback(t_log_event *event)
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

static void			file_callback(t_log_event *event)
{
	char		buf[64];

	format_time_stamp(event->tv, buf, sizeof(buf), "%Y-%m-%d %H:%M:%S");
	ft_dprintf(event->fd, "%s %-5s %s:%d: ", buf,
									g_loging_params.level_strings[event->level],
													event->file, event->line);
	ft_vdprintf(event->fd, event->fmt, event->ap);
	ft_dprintf(event->fd, "\n");
}

static void			lock(void)
{
	if (g_loging_params.lock)
	{
		g_loging_params.lock(1, g_loging_params.udata);
	}
}

static void			unlock(void)
{
	if (g_loging_params.lock)
	{
		g_loging_params.lock(1, g_loging_params.udata);
	}
}

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

void				ft_log_set_params(const char **level_strings,
													const char **level_colors)
{
	g_loging_params.level_strings = level_strings;
	g_loging_params.level_colors = level_colors;
	return ;
}

static void			execute_login_extensions(t_log_event *event,
														const char *fmt, ...)
{
	size_t					i;
	t_loging_extension		*loging_extension;

	i = -1;
	while (++i < MAX_LOGING_EXTENSIONS)
	{
		if (g_loging_params.loging_extensions[i])
		{
			loging_extension = g_loging_params.loging_extensions[i];
			if (event->level >= loging_extension->level)
			{
				event->fd = loging_extension->fd;
				va_start(event->ap, fmt);
				loging_extension->fn(event);
				va_end(event->ap);
			}
		}
	}
	return ;
}

void				ft_login_event(int level, const char *file, int line,
														const char *fmt, ...)
{
	t_log_event				event;

	event.fmt = fmt;
	event.file = file;
	event.line = line;
	event.level = level;
	gettimeofday(&event.tv, NULL);
	lock();
	if (!g_loging_params.quiet && level >= g_loging_params.level)
	{
		event.fd = 2;
		va_start(event.ap, fmt);
		stdout_callback(&event);
		va_end(event.ap);
	}
	execute_login_extensions(&event, fmt);
	unlock();
	return ;
}

void				ft_log_trace(const char *fmt, ...)
{
	t_log_event				event;

	event.fmt = fmt;
	event.file = __FILE__;
	event.line = __LINE__;
	event.level = LOG_TRACE;
	gettimeofday(&event.tv, NULL);
	lock();
	if (!g_loging_params.quiet && event.level >= g_loging_params.level)
	{
		event.fd = 2;
		va_start(event.ap, fmt);
		stdout_callback(&event);
		va_end(event.ap);
	}
	execute_login_extensions(&event, fmt);
	unlock();
	return ;
}

void				ft_log_debug(const char *fmt, ...)
{
	t_log_event				event;

	event.fmt = fmt;
	event.file = __FILE__;
	event.line = __LINE__;
	event.level = LOG_DEBUG;
	gettimeofday(&event.tv, NULL);
	lock();
	if (!g_loging_params.quiet && event.level >= g_loging_params.level)
	{
		event.fd = 2;
		va_start(event.ap, fmt);
		stdout_callback(&event);
		va_end(event.ap);
	}
	execute_login_extensions(&event, fmt);
	unlock();
	return ;
}

void				ft_log_info(const char *fmt, ...)
{
	t_log_event				event;

	event.fmt = fmt;
	event.file = __FILE__;
	event.line = __LINE__;
	event.level = LOG_INFO;
	gettimeofday(&event.tv, NULL);
	lock();
	if (!g_loging_params.quiet && event.level >= g_loging_params.level)
	{
		event.fd = 2;
		va_start(event.ap, fmt);
		stdout_callback(&event);
		va_end(event.ap);
	}
	execute_login_extensions(&event, fmt);
	unlock();
	return ;
}

void				ft_log_warn(const char *fmt, ...)
{
	t_log_event				event;

	event.fmt = fmt;
	event.file = __FILE__;
	event.line = __LINE__;
	event.level = LOG_WARN;
	gettimeofday(&event.tv, NULL);
	lock();
	if (!g_loging_params.quiet && event.level >= g_loging_params.level)
	{
		event.fd = 2;
		va_start(event.ap, fmt);
		stdout_callback(&event);
		va_end(event.ap);
	}
	execute_login_extensions(&event, fmt);
	unlock();
	return ;
}

void				ft_log_error(const char *fmt, ...)
{
	t_log_event				event;

	event.fmt = fmt;
	event.file = __FILE__;
	event.line = __LINE__;
	event.level = LOG_ERROR;
	gettimeofday(&event.tv, NULL);
	lock();
	if (!g_loging_params.quiet && event.level >= g_loging_params.level)
	{
		event.fd = 2;
		va_start(event.ap, fmt);
		stdout_callback(&event);
		va_end(event.ap);
	}
	execute_login_extensions(&event, fmt);
	unlock();
	return ;
}

void				ft_log_fatal(const char *fmt, ...)
{
	t_log_event				event;

	event.fmt = fmt;
	event.file = __FILE__;
	event.line = __LINE__;
	event.level = LOG_FATAL;
	gettimeofday(&event.tv, NULL);
	lock();
	if (!g_loging_params.quiet && event.level >= g_loging_params.level)
	{
		event.fd = 2;
		va_start(event.ap, fmt);
		stdout_callback(&event);
		va_end(event.ap);
	}
	execute_login_extensions(&event, fmt);
	unlock();
	return ;
}
