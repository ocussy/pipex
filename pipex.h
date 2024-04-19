/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:25:36 by ocussy            #+#    #+#             */
/*   Updated: 2024/04/19 16:43:38 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define READ_FD 0
# define WRITE_FD 1

typedef struct s_info
{
	int		nb_cmd;
	int		index;
	char	**argv;
	char	**cmd;
	char	**all_path;
	char	**all_path_modify;
	char	*good_path;
	char	*infile;
	char	*outfile;
	char	**env;
	char	**command_split;
	int		pid;
	int		open_file;
	int		fd[2];
	int		is_heredoc;
	char	*limiter;

}			t_info;

// FIND_PATH

char		*ft_command_path(t_info *src, int i);
char		**ft_make_tab(char **new_tab, t_info *src, char *word,
				int size_word);
char		**ft_modify_tab(t_info *src);
char		*ft_find_good_path(t_info *src);

// UTILS

void		ft_free_tab(char **tab);
int			ft_size_tab(char **tab);
int			ft_env_location(char **env);
char		*ft_find_word(t_info *src, char *argv);
void		ft_tab_cmd(t_info *src);

// UTILS_2

void		ft_exit(t_info *src, int i);
void		close_and_exit(t_info *src, int i);
char		*ft_clean_cmd(char *cmd);
void		ft_callexecve(t_info *src);

// PIPEX

void		ft_first_child(t_info *src, int i);
void		ft_last_child(t_info *src, int i);
void		ft_parent_process(t_info *src);
void		ft_pipex(t_info *src);
void		ft_wait_parent(t_info *src);

// MAKE_STRUCT

void		ft_init_src(t_info *src);
void		ft_make_struct(int argc, char **argv, char **env, t_info *src);

// PIPEX_MANDATORY

void		ft_child(t_info *src);
int			main(int argc, char **argv, char **env);

// PIPEX_BONUS

void		ft_middle_child(t_info *src, int i);
void		ft_child(t_info *src);
int			main(int argc, char **argv, char **env);

// UTILS_BONUS

void		ft_make_gnl(char *temp, char *line, t_info *src, int file);
void		ft_init_file(t_info *src);
void		ft_make_struct_heredoc(int argc, char **argv, char **env,
				t_info *src);

#endif