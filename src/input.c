/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 14:55:31 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/31 14:20:40 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			save_input_file(t_input *input, int *argc, char ***argv)
{
	if (*argc > 1)
	{
		if (!(input->opt & e_map_file))
		{
			input->input_file_path = ft_strdup((*argv)[1]);
			input->opt |= e_map_file;
		}
		ft_step_args(argc, argv);
	}
	else
		input->error = e_input_file_missing;
	return ;
}

static int		open_fd(t_input *input)
{
	int		fd;

	if (input->opt & e_map_file)
	{
		fd = open(input->input_file_path, O_RDONLY);
		if (fd < 0)
			input->error = e_file_open_failure;
	}
	else
		fd = 0;
	return (fd);
}

void			read_map_file(t_input *input)
{
	int			ret;
	char		*line;
	int			line_cnt;
	int			array_size;
	int			fd;

	if ((fd = open_fd(input)) >= 0)
	{
		line = NULL;
		array_size = 0;
		line_cnt = 0;
		while (!input->error && MAX_NUM_OF_LINES > line_cnt &&
										(ret = ft_get_next_line(fd, &line)) > 0)
		{
			input->point_map[line_cnt] =
					parse_map_line(line, &array_size, &input->error);
			line_cnt++;
			ft_strdel(&line);
		}
		ft_strdel(&line);
		input->map_size.x = array_size;
		input->map_size.y = line_cnt;
	}
	return ;
}

t_input			*read_command_attributes(int argc, char **argv)
{
	t_input		*input;

	ft_step_args(&argc, &argv);
	input = (t_input *)ft_memalloc(sizeof(*input));
	input->projection_plane = e_orthographic_top_view_line;
	input->error_string =
						(char **)ft_memalloc(sizeof(*input->error_string) * 11);
	input->point_map = (t_point **)ft_memalloc(sizeof(*input->point_map) *
															MAX_NUM_OF_LINES);
	input->width = WINDOW_WIDTH;
	input->hight = WINDOW_HIGHT;
	read_opt(input, &argc, &argv);
	return (input);
}
