/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:42:02 by ocussy            #+#    #+#             */
/*   Updated: 2024/04/09 18:29:16 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// int	ft_strlen(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (!str)
// 		return (0);
// 	while (str[i])
// 		i++;
// 	return (i);
// }

// int	ft_strchr(char *s)
// {
// 	int	i;

// 	i = 0;
// 	if (!s)
// 		return (0);
// 	while (s[i])
// 	{
// 		if (s[i] == '\n')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// void	ft_bzero(void *s, size_t n)
// {
// 	char	*str;
// 	size_t	i;

// 	str = (char *)s;
// 	i = 0;
// 	while (i < n)
// 	{
// 		str[i] = '\0';
// 		i++;
// 	}
// }

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	int		total_len;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s1)
		s1 = ft_calloc(1, 1);
	if (!s1)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc((total_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	*ft_make_join(char *line, char *buf)
{
	char	*tmp;

	tmp = ft_strjoin_gnl(line, buf);
	free(line);
	return (tmp);
}
