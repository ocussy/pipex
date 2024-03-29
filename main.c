/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:21:53 by ocussy            #+#    #+#             */
/*   Updated: 2024/03/28 11:35:19 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exit(int i)
{
	if (i == 1)
		ft_printf("Too few arguments.\n");
	if (i == 2)
		ft_printf("Error :%s\n", strerror(errno));
	if (i == 3)
		
	exit(0);
}

int	ft_env_location(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 4) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_size_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

char	*ft_find_word(char *argv)
{
	int		i;
	char	*word;
	int		j;

	i = 0;
	j = 0;
	word = NULL;
	while (argv[i] && ft_isalpha(argv[i]) == 1)
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (word == 0)
		return (NULL);
	while (j < i)
	{
		word[j] = argv[j];
		j++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_modify_tab(t_info *src)
{
	char	**new_tab;
	int		i;
	char	*word;
	int		size_word;

	i = 0;
	word = ft_find_word(src->cmd[src->index]);
	size_word = (int)ft_strlen(word);
	new_tab = (char **)malloc(sizeof(char *) * (ft_size_tab(src->all_path)
				+ 1));
	if (new_tab == NULL)
		ft_exit();
	while (src->all_path[i] != NULL)
	{
		new_tab[i] = (char *)malloc(ft_strlen(src->all_path[i] + size_word
					+ 1));
		if (new_tab[i] == NULL)
			ft_exit();
		ft_strlcpy(new_tab[i], src->all_path[i], ft_strlen(src->all_path[i])
			+ 1);
		ft_strlcat(new_tab[i], "/", ft_strlen(src->all_path[i]) + 2);
		ft_strlcat(new_tab[i], word, ft_strlen(new_tab[i]) + size_word + 1);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

char	*ft_find_good_path(t_info *src)
{
	int		i;
	char	*str;

	i = ft_env_location(src->env);
	if (i == -1)
		ft_exit();
	str = src->env[i] + 5;
	src->all_path = ft_split(str, ':');
	if (src->all_path == NULL)
		ft_exit();
	src->all_path = ft_modify_tab(src);
	i = 0;
	while (src->all_path[i])
	{
		if (access(src->all_path[i], F_OK) != -1 && access(src->all_path[i],
				R_OK) != -1)
		{
			printf("Le path %s est valide !\n", src->all_path[i]);
			return (src->all_path[i]);
		}
		i++;
	}
	return (NULL);
}

void	ft_tab_cmd(t_info *src)
{
	int	i;
	int	j;

	i = 0;
	j = 2;
	src->cmd = (char **)malloc(sizeof(char *) * src->nb_cmd + 1);
	if (src->cmd == NULL)
		ft_exit(2);
	while (i < src->nb_cmd)
	{
		src->cmd[i] = ft_strdup(src->argv[j]);
		if (src->cmd[i] == NULL)
			ft_exit(3);
		i++;
		j++;
	}
	src->cmd[i] = NULL;
}

void	ft_callexecve(t_info *src)
{
	execve(src->good_path, src->command_split, src->env);
	perror("execve");
	ft_exit();
}

void	ft_first_child(t_info *src, int i)
{
	printf("Je suis le premier processus enfant\n");
	close(src->fd[READ_FD]);
	src->good_path = ft_find_good_path(src);
	printf("Le bon path est %s\n", src->good_path);
	if (src->good_path == NULL)
		ft_exit();
	src->command_split = ft_split(src->cmd[i], ' ');
	dup2(src->fd[WRITE_FD], STDOUT_FILENO);
	dup2(src->open_file, STDIN_FILENO);
	close(src->open_file);
	close(src->fd[WRITE_FD]);
	ft_callexecve(src);
}

void	ft_middle_child(t_info *src, int i)
{
	src->good_path = ft_find_good_path(src);
	if (src->good_path == NULL)
		ft_exit();
	src->command_split = ft_split(src->cmd[i], ' ');
	dup2(src->fd[READ_FD], STDIN_FILENO);
	dup2(src->fd[WRITE_FD], STDOUT_FILENO);
	close(src->fd[READ_FD]);
	close(src->fd[WRITE_FD]);
	ft_callexecve(src);
}

void	ft_last_child(t_info *src, int i)
{
	int	fd_file;

	close(src->fd[WRITE_FD]);
	src->good_path = ft_find_good_path(src);
	if (src->good_path == NULL)
		ft_exit();
	src->command_split = ft_split(src->cmd[i], ' ');
	fd_file = open(src->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd_file == -1)
		ft_exit();
	dup2(fd_file, STDOUT_FILENO);
	dup2(src->fd[READ_FD], STDIN_FILENO);
	close(src->fd[READ_FD]);
	close(fd_file);
	ft_callexecve(src);
}

void	ft_wait_parent(void)
{
	while (errno != ECHILD)
		wait(NULL);
}

void	ft_parent_process(t_info *src)
{
	close(src->fd[WRITE_FD]);
	dup2(src->fd[READ_FD], STDOUT_FILENO);
	close(src->fd[READ_FD]);
}

void	ft_pipex(t_info *src)
{
	int	i;

	i = 0;
	src->open_file = open(src->infile, O_RDONLY);
	if (src->open_file == -1)
		ft_exit(2);
	ft_tab_cmd(src);
	i = 0;
	while (i < src->nb_cmd)
	{
		if (pipe(src->fd) == -1)
			ft_exit(2);
		src->pid = fork();
		if (src->pid == -1)
			ft_exit(2);
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
	}
	ft_wait_parent();
}

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
}

void	ft_make_struct(int argc, char **argv, char **env, t_info *src)
{
	int	i;
	int	j;

	i = 2;
	j = 0;
	ft_init_src(src);
	src->index = 0;
	src->nb_cmd = argc - 3;
	src->infile = argv[1];
	src->outfile = argv[argc - 1];
	src->env = env;
	src->argv = argv;
}

int	main(int argc, char **argv, char **env)
{
	t_info	src;

	if (argc > 4)
	{
		ft_make_struct(argc, argv, env, &src);
		ft_pipex(&src);
	}
	else
	{
		ft_exit(1);
	}
	return (0);
}
