/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:48:14 by ocussy            #+#    #+#             */
/*   Updated: 2024/04/19 16:43:34 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_middle_child(t_info *src, int i)
{
	src->good_path = ft_find_good_path(src);
	if (src->good_path == NULL)
		src->good_path = ft_command_path(src, i);
	if (src->good_path == NULL)
		close_and_exit(src, 3);
	src->command_split = ft_split(src->cmd[i], ' ');
	dup2(src->fd[WRITE_FD], STDOUT_FILENO);
	close(src->fd[READ_FD]);
	close(src->fd[WRITE_FD]);
	ft_callexecve(src);
}

void	ft_child(t_info *src)
{
	int	i;

	i = 0;
	while (i < src->nb_cmd)
	{
		if (pipe(src->fd) == -1)
			ft_exit(src, 2);
		src->pid = fork();
		if (src->pid == -1)
			close_and_exit(src, 2);
		else if (src->pid == 0)
		{
			if (i == 0)
				ft_first_child(src, i);
			else if (i == (src->nb_cmd - 1))
				ft_last_child(src, i);
			else
				ft_middle_child(src, i);
			exit(EXIT_SUCCESS);
		}
		i++;
		src->index++;
		ft_parent_process(src);
	}
	ft_wait_parent(src);
}

int	main(int argc, char **argv, char **env)
{
	t_info	src;

	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
		ft_make_struct_heredoc(argc, argv, env, &src);
	else
		ft_make_struct(argc, argv, env, &src);
	if (argc > 4 && src.is_heredoc == 0)
		ft_pipex(&src);
	else if (argc > 5 && src.is_heredoc == 1)
		ft_pipex(&src);
	else
		ft_exit(&src, 1);
	return (0);
}
