/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:50:32 by ocussy            #+#    #+#             */
/*   Updated: 2024/04/19 16:28:22 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	**ft_make_tab(char **new_tab, t_info *src, char *word, int size_word)
{
	int	i;

	i = 0;
	while (src->all_path[i] != NULL)
	{
		new_tab[i] = (char *)malloc(ft_strlen(src->all_path[i]) + size_word
				+ 2);
		if (new_tab[i] == NULL)
		{
			ft_free_tab(new_tab);
			close_and_exit(src, 2);
		}
		ft_strlcpy(new_tab[i], src->all_path[i], ft_strlen(src->all_path[i])
			+ 1);
		ft_strlcat(new_tab[i], "/", ft_strlen(src->all_path[i]) + 2);
		ft_strlcat(new_tab[i], word, ft_strlen(new_tab[i]) + size_word + 1);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

char	**ft_modify_tab(t_info *src)
{
	char	**new_tab;
	char	*word;
	int		size_word;

	word = ft_find_word(src, src->cmd[src->index]);
	if (word == NULL)
		close_and_exit(src, 2);
	size_word = (int)ft_strlen(word);
	new_tab = (char **)malloc(sizeof(char *) * (ft_size_tab(src->all_path)
				+ 1));
	if (new_tab == NULL)
		close_and_exit(src, 2);
	new_tab = ft_make_tab(new_tab, src, word, size_word);
	free(word);
	return (new_tab);
}

char	*ft_find_good_path(t_info *src)
{
	char	*str;
	char	*good_path;
	int		i;

	good_path = NULL;
	i = ft_env_location(src->env);
	if (i == -1)
		close_and_exit(src, 3);
	str = src->env[i] + 5;
	if (!src->all_path)
		src->all_path = ft_split(str, ':');
	if (src->all_path == NULL)
		close_and_exit(src, 2);
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
