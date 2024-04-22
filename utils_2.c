/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:59:56 by ocussy            #+#    #+#             */
/*   Updated: 2024/04/22 16:40:04 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exit(t_info *src, int i)
{
	if (i == 1)
		ft_printf("Wrong number of arguments.\n");
	if (i == 2)
		ft_printf("Error :%s\n", strerror(errno));
	if (i == 3)
		ft_printf("No path found or wrong command\n");
	if (i == 4)
		ft_printf("Wrong command\n");
	if (i == 5)
		ft_printf("Problem leaving here_doc\n");
	if (src->command_split != NULL)
		ft_free_tab(src->command_split);
	if (src->cmd != NULL)
		ft_free_tab(src->cmd);
	if (src->all_path != NULL)
		ft_free_tab(src->all_path);
	if (src->all_path_modify)
		ft_free_tab(src->all_path_modify);
	if (src->good_path)
		free(src->good_path);
	if (src->is_heredoc == 1)
		unlink("heredoc.txt");
	exit(1);
}

void	close_and_exit(t_info *src, int i)
{
	close(src->fd[READ_FD]);
	close(src->fd[WRITE_FD]);
	ft_exit(src, i);
}

char	*ft_clean_cmd(char *cmd)
{
	int	i;
	int	j;

	i = (int)ft_strlen(cmd);
	j = 0;
	while (cmd[i] != '/')
	{
		i--;
		j++;
	}
	while (*cmd && (int)ft_strlen(cmd) != j)
		cmd++;
	cmd++;
	return (cmd);
}

void	ft_callexecve(t_info *src)
{
	execve(src->good_path, src->command_split, src->env);
	perror("execve");
	close_and_exit(src, 2);
}
