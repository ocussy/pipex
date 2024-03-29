/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:25:36 by ocussy            #+#    #+#             */
/*   Updated: 2024/03/28 11:04:42 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
#include <errno.h>
#include "./ft_printf/ft_printf.h"

# define READ_FD 0
# define WRITE_FD 1

typedef struct s_info
{
	int		nb_cmd;
	int		index;
	char	**argv;
	char	**cmd;
	char	**all_path;
	char	*good_path;
	char	*infile;
	char	*outfile;
	char	**env;
	char	**command_split;
	int		pid;
	int		open_file;
	int fd[2];

}			t_info;

#endif