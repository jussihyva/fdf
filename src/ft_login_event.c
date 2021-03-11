/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_login_event.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 10:22:34 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/11 11:48:17 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_loging_params		g_loging_params;

static void		format_time_stamp(struct timeval tv, char *time_string, size_t size, char *format_string)
{
	int			millisec;
	struct tm	*tm_info;

	millisec = lrint(tv.tv_usec/1000.0);
	if (millisec>=1000)
	{
		millisec -=1000;
		tv.tv_sec++;
	}
	tm_info = localtime(&tv.tv_sec);
	strftime(time_string, size, format_string, tm_info);
	ft_sprintf(time_string + ft_strlen(format_string), ".%03d", millisec);
	return ;
}

static void stdout_callback(t_log_event *event)
{
	char		buf[16];

	format_time_stamp(event->tv, buf, sizeof(buf), "%H:%M:%S");
#ifdef LOG_USE_COLOR
	fprintf(
		event->udata, "%s %s%-5s\x1b[0m \x1b[90m%s:%d:\x1b[0m ",
		buf, g_loging_params.level_colors[event->level], g_loging_params.level_strings[event->level],
		event->file, event->line);
#else
	fprintf(
		event->udata, "%s %-5s %s:%d: ",
		buf, g_loging_params.level_strings[event->level], event->file, event->line);
#endif
	vfprintf(event->udata, event->fmt, event->ap);
	fprintf(event->udata, "\n");
	fflush(event->udata);
}

static void file_callback(t_log_event *event)
{
	char		buf[64];

	format_time_stamp(event->tv, buf, sizeof(buf), "%Y-%m-%d %H:%M:%S");
	fprintf(event->udata, "%s %-5s %s:%d: ", buf, g_loging_params.level_strings[event->level],
													event->file, event->line);
	vfprintf(event->udata, event->fmt, event->ap);
	fprintf(event->udata, "\n");
	fflush(event->udata);
}

static void lock(void)
{
	if (g_loging_params.lock)
	{
		g_loging_params.lock(1, g_loging_params.udata);
	}
}

static void unlock(void)
{
	if (g_loging_params.lock)
	{
		g_loging_params.lock(1, g_loging_params.udata);
	}
}

const char* log_level_string(int level)
{
	return g_loging_params.level_strings[level];
}

void log_set_lock(loging_lock_function fn, void *udata)
{
	g_loging_params.lock = fn;
	g_loging_params.udata = udata;
}

void ft_log_set_level(int level)
{
	g_loging_params.level = level;
}

void log_set_quiet(int enable)
{
	g_loging_params.quiet = enable;
}

int log_add_callback(loging_function fn, void *udata, int level)
{
	t_loging_extension		*loging_extension;
	size_t					i;

	loging_extension = (t_loging_extension *)ft_memalloc(sizeof(*loging_extension));
	loging_extension->fn = fn;
	loging_extension->udata = udata;
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

int log_add_fp(FILE *fp, int level)
{
	return log_add_callback(file_callback, fp, level);
}

static void init_event(t_log_event *event, void *udata)
{
	event->udata = udata;
}

void	ft_log_set_params(const char **level_strings, const char **level_colors)
{
	g_loging_params.level_strings = level_strings;
	g_loging_params.level_colors = level_colors;
	return ;
}

void 	ft_login_event(int level, const char *file, int line, const char *fmt, ...)
{
	t_log_event				event;
	t_loging_extension		*loging_extension;
	size_t					i;
	
	event.fmt = fmt;
	event.file = file;
	event.line = line;
	event.level = level;
	gettimeofday(&event.tv, NULL);
	lock();
	if (!g_loging_params.quiet && level >= g_loging_params.level)
	{
		init_event(&event, stderr);
		va_start(event.ap, fmt);
		stdout_callback(&event);
		va_end(event.ap);
	}
	i = -1;
	while (++i < MAX_LOGING_EXTENSIONS)
	{
		if (g_loging_params.loging_extensions[i])
		{
			loging_extension = g_loging_params.loging_extensions[i];
			if (level >= loging_extension->level)
			{
				init_event(&event, loging_extension->udata);
				va_start(event.ap, fmt);
				loging_extension->fn(&event);
				va_end(event.ap);
			}
		}
	}
	unlock();
	return ;
}
