/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:24:08 by ocussy            #+#    #+#             */
/*   Updated: 2024/04/22 16:43:15 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exit_sig(char *line, t_info *src, int i)
{
	if (i == 1)
		free(line);
	free(src->limiter);
	ft_exit(src, 5);
}

char	*ft_while_gnl(char *temp, char *line, char *buffer)
{
	temp = ft_strjoin(line, buffer);
	free(line);
	free(buffer);
	line = temp;
	return (line);
}

void	ft_make_gnl(char *temp, char *line, t_info *src, int file)
{
	char	*buffer;

	src->i = 0;
	buffer = get_next_line(READ_FD);
	if (buffer == NULL)
		ft_exit_sig(line, src, 0);
	if (ft_strncmp(buffer, src->limiter, (ft_strlen(src->limiter) + 1)) != 0)
	{
		line = buffer;
		while (1)
		{
			buffer = get_next_line(READ_FD);
			if (buffer == NULL)
				ft_exit_sig(line, src, 1);
			src->i++;
			if (ft_strncmp(buffer, src->limiter, (ft_strlen(src->limiter)
						+ 1)) == 0)
				break ;
			line = ft_while_gnl(temp, line, buffer);
		}
	}
	write(file, line, ft_strlen(line));
	if (src->i >= 1)
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
	src->infile = "heredoc.txt";
	src->is_heredoc = 1;
	ft_init_file(src);
}
