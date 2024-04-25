/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:21:53 by ocussy            #+#    #+#             */
/*   Updated: 2024/04/25 09:42:33 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_first_child(t_info *src, int i)
{
	src->open_file = open(src->infile, O_RDONLY);
	if (src->is_heredoc == 1)
		unlink("heredoc.txt");
	if (src->open_file == -1)
		close_and_exit(src, 2);
	close(src->fd[READ_FD]);
	src->good_path = ft_find_good_path(src);
	src->command_split = ft_split(src->cmd[i], ' ');
	if (src->good_path == NULL)
	{
		src->good_path = ft_command_path(src, i);
		ft_free_tab(src->command_split);
		src->command_split = ft_split(src->cmd[i], ' ');
	}
	if (src->good_path == NULL)
		close_and_exit(src, 3);
	dup2(src->fd[WRITE_FD], STDOUT_FILENO);
	dup2(src->open_file, STDIN_FILENO);
	close(src->open_file);
	close(src->fd[WRITE_FD]);
	ft_callexecve(src);
}

void	ft_last_child(t_info *src, int i)
{
	int	fd_file;

	close(src->fd[WRITE_FD]);
	close(src->fd[READ_FD]);
	src->good_path = ft_find_good_path(src);
	if (src->good_path == NULL)
		src->good_path = ft_command_path(src, i);
	if (src->good_path == NULL)
		close_and_exit(src, 3);
	src->command_split = ft_split(src->cmd[i], ' ');
	fd_file = open(src->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd_file == -1)
		close_and_exit(src, 2);
	dup2(fd_file, STDOUT_FILENO);
	close(fd_file);
	ft_callexecve(src);
}

void	ft_parent_process(t_info *src)
{
	close(src->fd[WRITE_FD]);
	dup2(src->fd[READ_FD], STDIN_FILENO);
	close(src->fd[READ_FD]);
}

void	ft_pipex(t_info *src)
{
	int	i;

	i = 0;
	ft_tab_cmd(src);
	ft_child(src);
	ft_free_tab(src->cmd);
}

void	ft_wait_parent(t_info *src)
{
	waitpid(src->pid, NULL, 0);
	while (wait(NULL) != -1)
	{
	}
}
