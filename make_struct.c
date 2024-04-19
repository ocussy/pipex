/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:18:31 by ocussy            #+#    #+#             */
/*   Updated: 2024/04/19 16:44:57 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_init_src(t_info *src)
{
	src->nb_cmd = 0;
	src->index = 0;
	src->pid = -1;
	src->open_file = -1;
	src->all_path = NULL;
	src->env = NULL;
	src->cmd = NULL;
	src->infile = NULL;
	src->outfile = NULL;
	src->argv = NULL;
	src->command_split = NULL;
	src->all_path_modify = NULL;
}

void	ft_make_struct(int argc, char **argv, char **env, t_info *src)
{
	ft_init_src(src);
	src->nb_cmd = 2;
	src->infile = argv[1];
	src->is_heredoc = 0;
	src->outfile = argv[argc - 1];
	src->env = env;
	src->argv = argv;
}
