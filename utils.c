/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:48:28 by ocussy            #+#    #+#             */
/*   Updated: 2024/04/19 11:51:13 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i] != NULL)
	{
		if (tab[i] != NULL)
		{
			free(tab[i]);
			tab[i] = NULL;
		}
		i++;
	}
	free(tab);
	tab = NULL;
}

int	ft_size_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
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

char	*ft_find_word(t_info *src, char *argv)
{
	int		i;
	char	**word_split;
	char	*word;
	int		j;

	i = 0;
	j = 0;
	word_split = ft_split(argv, ' ');
	if (word_split == NULL || word_split[0] == NULL)
	{
		if (word_split != NULL)
			ft_free_tab(word_split);
		close_and_exit(src, 4);
	}
	word = ft_strdup(word_split[0]);
	ft_free_tab(word_split);
	return (word);
}

void	ft_tab_cmd(t_info *src)
{
	int	i;
	int	j;

	if (src->is_heredoc == 1)
		j = 3;
	else
		j = 2;
	i = 0;
	src->cmd = (char **)malloc(sizeof(char *) * (src->nb_cmd + 1));
	if (src->cmd == NULL)
		ft_exit(src, 2);
	while (i < src->nb_cmd && src->argv[j])
	{
		src->cmd[i] = ft_strdup(src->argv[j]);
		if (src->cmd[i] == NULL)
			ft_exit(src, 2);
		i++;
		j++;
	}
	src->cmd[i] = NULL;
}
