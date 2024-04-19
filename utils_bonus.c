/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:24:08 by ocussy            #+#    #+#             */
/*   Updated: 2024/04/19 16:38:38 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_make_gnl(char *temp, char *line, t_info *src, int file)
{
	char	*buffer;
	int		i;

	i = 0;
	buffer = get_next_line(READ_FD);
	if (ft_strncmp(buffer, src->limiter, (ft_strlen(src->limiter) + 1)) != 0)
	{
		line = buffer;
		while (1)
		{
			buffer = get_next_line(READ_FD);
			++i;
			if (ft_strncmp(buffer, src->limiter, (ft_strlen(src->limiter)
						+ 1)) == 0)
				break ;
			temp = ft_strjoin(line, buffer);
			free(line);
			free(buffer);
			line = temp;
		}
	}
	write(file, line, ft_strlen(line));
	if (i >= 1)
		free(line);
	free(buffer);
}

void	ft_init_file(t_info *src)
{
	int		file;
	char	*line;
	int		i;
	char	*temp;

	line = "";
	temp = "";
	i = 0;
	file = open("heredoc.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (file == -1)
		ft_exit(src, 2);
	ft_make_gnl(temp, line, src, file);
	free(src->limiter);
	close(file);
}

void	ft_make_struct_heredoc(int argc, char **argv, char **env, t_info *src)
{
	ft_init_src(src);
	src->nb_cmd = argc - 4;
	src->outfile = argv[argc - 1];
	src->env = env;
	src->argv = argv;
	src->limiter = ft_strjoin(argv[2], "\n");
	ft_init_file(src);
	src->infile = "heredoc.txt";
	src->is_heredoc = 1;
}
