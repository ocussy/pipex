/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:21:53 by ocussy            #+#    #+#             */
/*   Updated: 2024/04/10 11:54:39 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i] != NULL)
			free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_exit(t_info *src, int i)
{
	if (i == 1)
		ft_printf("Too few arguments.\n");
	if (i == 2)
		ft_printf("Error :%s\n", strerror(errno));
	if (i == 3)
		ft_printf("No path found \n");
	if (i == 4)
		ft_printf("Wrong command\n");
	if (src->command_split)
		ft_free_tab(src->command_split);
	if (src->cmd)
		ft_free_tab(src->cmd);
	if (src->all_path)
		ft_free_tab(src->all_path);
	if (src->all_path_modify)
		ft_free_tab(src->all_path_modify);
	exit(1);
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

char	*ft_find_word(t_info *src, char *argv)
{
	int		i;
	char	**word_split;
	char	*word;
	int		j;

	i = 0;
	j = 0;
	word_split = ft_split(argv, ' ');
	printf("%s\n", word_split[0]);
	if (word_split == NULL || word_split[0] == NULL)
	{
		if (word_split != NULL)
			ft_free_tab(word_split);
		ft_exit(src, 4);
	}
	word = ft_strdup(word_split[0]);
	ft_free_tab(word_split);
	return (word);
}

char	**ft_modify_tab(t_info *src)
{
	char	**new_tab;
	int		i;
	char	*word;
	int		size_word;

	i = 0;
	printf("index = %d\n", src->index);
	word = ft_find_word(src, src->cmd[src->index]);
	if (word == NULL)
		ft_exit(src, 2);
	size_word = (int)ft_strlen(word);
	new_tab = (char **)malloc(sizeof(char *) * (ft_size_tab(src->all_path)
				+ 1));
	if (new_tab == NULL)
		ft_exit(src, 2);
	while (src->all_path[i] != NULL)
	{
		new_tab[i] = (char *)malloc(ft_strlen(src->all_path[i]) + size_word
				+ 2);
		if (new_tab[i] == NULL)
		{
			ft_free_tab(new_tab);
			ft_exit(src, 2);
		}
		ft_strlcpy(new_tab[i], src->all_path[i], ft_strlen(src->all_path[i])
			+ 1);
		ft_strlcat(new_tab[i], "/", ft_strlen(src->all_path[i]) + 2);
		ft_strlcat(new_tab[i], word, ft_strlen(new_tab[i]) + size_word + 1);
		i++;
	}
	new_tab[i] = NULL;
	free(word);
	return (new_tab);
}

char	*ft_find_good_path(t_info *src)
{
	int		i;
	char	*str;
	char	*good_path;

	good_path = NULL;
	i = ft_env_location(src->env);
	if (i == -1)
		ft_exit(src, 3);
	str = src->env[i] + 5;
	if (!src->all_path)
		src->all_path = ft_split(str, ':');
	if (src->all_path == NULL)
		ft_exit(src, 2);
	src->all_path_modify = ft_modify_tab(src);
	i = 0;
	while (src->all_path[i])
	{
		if (access(src->all_path_modify[i], F_OK) != -1
			&& access(src->all_path_modify[i], R_OK) != -1)
			good_path = ft_strdup(src->all_path_modify[i]);
		i++;
	}
	return (good_path);
}

void	ft_tab_cmd(t_info *src)
{
	int	i;
	int	j;

	i = 0;
	j = 2;
	src->cmd = (char **)malloc(sizeof(char *) * (src->nb_cmd + 1));
	if (src->cmd == NULL)
		ft_exit(src, 2);
	while (i < src->nb_cmd)
	{
		src->cmd[i] = ft_strdup(src->argv[j]);
		if (src->cmd[i] == NULL)
			ft_exit(src, 2);
		i++;
		j++;
	}
	src->cmd[i] = NULL;
}

char	*ft_command_path(t_info *src, int i)
{
	char	**command_split;
	char	*command_path;

	command_path = NULL;
	command_split = ft_split(src->cmd[i], ' ');
	if (access(command_split[0], F_OK) != -1 && access(command_split[0],
			R_OK) != -1)
		command_path = ft_strdup(command_split[0]);
	ft_free_tab(command_split);
	return (command_path);
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
	while ((int)ft_strlen(cmd) != j)
		cmd++;
	cmd++;
	return (cmd);
}

void	ft_callexecve(t_info *src)
{
	execve(src->good_path, src->command_split, src->env);
	perror("execve");
	ft_exit(src, 2);
}

void	ft_first_child(t_info *src, int i)
{
	close(src->fd[READ_FD]);
	src->good_path = ft_find_good_path(src);
	src->command_split = ft_split(src->cmd[i], ' ');
	if (src->good_path == NULL)
	{
		src->good_path = ft_command_path(src, i);
		ft_free_tab(src->command_split);
		src->cmd[i] = ft_clean_cmd(src->cmd[i]);
		src->command_split = ft_split(src->cmd[i], ' ');
	}
	if (src->good_path == NULL)
		ft_exit(src, 3);
	dup2(src->fd[WRITE_FD], STDOUT_FILENO);
	dup2(src->open_file, STDIN_FILENO);
	close(src->open_file);
	close(src->fd[WRITE_FD]);
	ft_callexecve(src);
}

void	ft_middle_child(t_info *src, int i)
{
	close(src->fd[READ_FD]);
	src->good_path = ft_find_good_path(src);
	if (src->good_path == NULL)
		src->good_path = ft_command_path(src, i);
	if (src->good_path == NULL)
		ft_exit(src, 3);
	src->command_split = ft_split(src->cmd[i], ' ');
	dup2(src->open_file, STDIN_FILENO);
	dup2(src->fd[WRITE_FD], STDOUT_FILENO);
	close(src->open_file);
	close(src->fd[WRITE_FD]);
	ft_callexecve(src);
}

void	ft_last_child(t_info *src, int i)
{
	int	fd_file;

	close(src->fd[READ_FD]);
	close(src->fd[WRITE_FD]);
	src->good_path = ft_find_good_path(src);
	if (src->good_path == NULL)
		src->good_path = ft_command_path(src, i);
	if (src->good_path == NULL)
		ft_exit(src, 3);
	src->command_split = ft_split(src->cmd[i], ' ');
	fd_file = open(src->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd_file == -1)
		ft_exit(src, 2);
	dup2(fd_file, STDOUT_FILENO);
	dup2(src->open_file, STDIN_FILENO);
	close(src->open_file);
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
	close(src->open_file);
	src->open_file = src->fd[READ_FD];
}

void	ft_pipex(t_info *src)
{
	int	i;

	src->open_file = open(src->infile, O_RDONLY);
	printf("%s\n", src->infile);
	if (src->open_file == -1)
		ft_exit(src, 2);
	ft_tab_cmd(src);
	i = 0;
	while (i < src->nb_cmd)
	{
		if (pipe(src->fd) == -1)
			ft_exit(src, 2);
		src->pid = fork();
		if (src->pid == -1)
			ft_exit(src, 2);
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
	ft_free_tab(src->cmd);
	ft_wait_parent();
}

void	ft_init_file(t_info *src)
{
	int		file;
	char	*line;
	char	*buffer;
	int		i;

	i = 0;
	line = NULL;
	file = open("heredoc.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	// unlink(".heredoc.txt");
	if (file == -1)
		ft_exit(src, 2);
	buffer = get_next_line(0);
	while (ft_strncmp(buffer, src->limiter, (ft_strlen(src->limiter) + 1)) != 0)
	{
		if (i == 0)
			line = buffer;
		else
		{
			line = ft_strjoin(line, buffer);
			free(buffer);
		}
		buffer = get_next_line(0);
		++i;
	}
	write(file, line, ft_strlen(line));
	close(file);
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
	src->all_path_modify = NULL;
}

void	ft_make_struct(int argc, char **argv, char **env, t_info *src)
{
	ft_init_src(src);
	src->nb_cmd = argc - 3;
	src->infile = argv[1];
	src->outfile = argv[argc - 1];
	src->env = env;
	src->argv = argv;
}

void	ft_make_struct_heredoc(int argc, char **argv, char **env, t_info *src)
{
	ft_init_src(src);
	src->nb_cmd = argc - 4;
	src->index = 1;
	src->outfile = argv[argc - 1];
	src->env = env;
	src->argv = argv;
	src->limiter = ft_strjoin(argv[2], "\n");
	ft_init_file(src);
	src->infile = "heredoc.txt";
}

int	main(int argc, char **argv, char **env)
{
	t_info	src;

	if (argc > 4)
	{
		if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
			ft_make_struct_heredoc(argc, argv, env, &src);
		else
			ft_make_struct(argc, argv, env, &src);
		ft_pipex(&src);
	}
	else
	{
		ft_exit(&src, 1);
	}
	return (0);
}
