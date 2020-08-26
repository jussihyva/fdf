/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 14:55:31 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/26 11:12:03 by jkauppi          ###   ########.fr       */
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

	fd = 0;
	if (input->opt & e_map_file)
		fd = open(input->input_file_path, O_RDONLY);
	return (fd);
}

static void		read_map_file(int fd, t_input *input)
{
	int			ret;
	char		*line;
	int			array_size;

	line = NULL;
	array_size = 0;
	while (!input->error && MAX_NUM_OF_LINES > input->input_array_size &&
										(ret = ft_get_next_line(fd, &line)) > 0)
	{
		ft_printf("%s\n", line);
		input->input_line_array[input->input_array_size] = line;
		input->point_array[input->input_array_size] =
											parse_map_line(line, &array_size);
		if (!array_size)
			input->error = e_input_file_parse_error;
		input->input_array_size++;
		ft_strdel(&line);
	}
	ft_strdel(&line);
	ft_printf("Lines in the file (%s): %d\n", input->input_file_path,
													input->input_array_size);
	return ;
}

t_input			*read_input_data(int argc, char **argv)
{
	t_input		*input;
	int			fd;

	input = (t_input *)ft_memalloc(sizeof(*input));
	input->error_string =
					(char **)ft_memalloc(sizeof(*input->error_string) * 11);
	input->input_line_array =
						(char **)ft_memalloc(sizeof(*input->input_line_array) *
															MAX_NUM_OF_LINES);
	input->point_array =
						(t_point **)ft_memalloc(sizeof(*input->point_array) *
															MAX_NUM_OF_LINES);
	read_opt(input, &argc, &argv);
	fd = open_fd(input);
	if (fd < 0)
		input->error = e_file_open_failure;
	else
		read_map_file(fd, input);
	return (input);
}
