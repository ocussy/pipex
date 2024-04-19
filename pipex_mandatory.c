/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_mandatory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:48:06 by ocussy            #+#    #+#             */
/*   Updated: 2024/04/19 16:50:57 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
			else
				ft_last_child(src, i);
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

	ft_make_struct(argc, argv, env, &src);
	if (argc == 5)
		ft_pipex(&src);
	else
		ft_exit(&src, 1);
	return (0);
}
