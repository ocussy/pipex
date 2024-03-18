/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:21:53 by ocussy            #+#    #+#             */
/*   Updated: 2024/03/18 18:58:15 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exit(void)
{
	perror("Une erreur s'est produite\n");
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

char	**ft_modify_tab(char **tab, char *argv)
{
	char	**new_tab;
	int		i;
	char	*word;
	int		size_word;

	i = 0;
	word = ft_find_word(argv);
	printf("Le mot est %s\n", word);
	size_word = (int)ft_strlen(word);
	new_tab = (char **)malloc(sizeof(char *) * (ft_size_tab(tab) + 1));
	if (new_tab == NULL)
		ft_exit();
	while (tab[i] != NULL)
	{
		new_tab[i] = (char *)malloc(ft_strlen(tab[i] + size_word + 1));
		if (new_tab[i] == NULL)
			ft_exit();
		ft_strlcpy(new_tab[i], tab[i])
	}
	return (tab);
}

char	*ft_find_path(char **argv, char **env)
{
	int		i;
	char	*str;
	char	**tab;

	i = ft_env_location(env);
	if (i == -1)
		ft_exit();
	str = env[i] + 5;
	tab = ft_split(str, ':');
	tab = ft_modify_tab(tab, argv[2]);
	// i = 0;
	// while (tab[i] != NULL)
	// {
	// 	ft_strlcat(tab[i], "/", sizeof(tab[i]));
	// 	printf("La case %d du tableau est : %s\n", i, tab[i]);
	// 	i++;
	// }
	return (0);
}

int	ft_verif(int argc, char **argv, char **env)
{
	int		file1;
	int		fd[2];
	int		id;
	char	*path;

	path = NULL;
	// printf("Il y a %d arguments dont %s\n", argc, argv[1]);
	file1 = open(argv[1], O_RDONLY);
	if (file1 == -1)
		ft_exit();
	if (pipe(fd) == -1)
		ft_exit();
	id = fork();
	if (id == -1)
		ft_exit();
	if (id == 0)
	{
		path = ft_find_path(argv, env);
		// if (path == NULL)
		// 	ft_exit();
		// trouver le path dans ENV
		// split le path
		// rajouter les /
		// rajouter la commande a la fin
		// chercher avec access dans chaque path
	}
	if (id != 0)
		wait(0);
	printf("Le fichier %d a pu s'ouvrir", argc);
	close(file1);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	if (argc > 4)
		ft_verif(argc, argv, env);
	else
	{
		ft_exit();
	}
	return (0);
}
