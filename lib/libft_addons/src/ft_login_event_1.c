/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_login_event_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 10:22:34 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/23 08:29:54 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

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
