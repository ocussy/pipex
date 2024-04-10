/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:54:37 by ocussy            #+#    #+#             */
/*   Updated: 2024/04/09 18:29:40 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	char	*res;

	res = malloc(elementSize * elementCount);
	if (!res)
		return (NULL);
	ft_bzero(res, elementSize * elementCount);
	return (res);
}

char	*ft_make_line(int fd, char *line)
{
	char	*buf;
	int		count;

	if (!line)
		line = ft_calloc(1, 1);
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	count = 1;
	while (count > 0)
	{
		count = read(fd, buf, BUFFER_SIZE);
		if (count == -1 || (count == 0 && line[0] == '\0'))
		{
			free(buf);
			free(line);
			return (NULL);
		}
		buf[count] = '\0';
		line = ft_make_join(line, buf);
		if (count != BUFFER_SIZE || ft_strchr(buf, '\n') != 0)
			break ;
	}
	free(buf);
	return (line);
}

char	*ft_get_line(char *tempo)
{
	char	*line;
	int		i;

	i = 0;
	if (!tempo)
		return (NULL);
	while (tempo[i] && tempo[i] != '\n')
		i++;
	line = ft_calloc((i + 2), sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (tempo[i] && tempo[i] != '\n')
	{
		line[i] = tempo[i];
		i++;
	}
	if (tempo[i] && tempo[i] == '\n')
	{
		line[i] = tempo[i];
		i++;
	}
	return (line);
}

char	*ft_clean(char *line)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	if (!line)
	{
		free(line);
		return (NULL);
	}
	while (line[i] != '\n' && line[i])
		i++;
	tmp = ft_calloc((ft_strlen(line) - i + 1), sizeof(char));
	if (!tmp)
	{
		free(line);
		return (NULL);
	}
	if (line[i] && line[i] == '\n')
		i++;
	while (line[i])
		tmp[j++] = line[i++];
	free(line);
	return (tmp);
}

char	*get_next_line(int fd)
{
	char		*final_line;
	static char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_make_line(fd, line);
	if (!line || *line == '\0')
	{
		free(line);
		return (NULL);
	}
	final_line = ft_get_line(line);
	line = ft_clean(line);
	return (final_line);
}

// static char	*ft_join(char *s1, char *s2, char *str)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	j = 0;
// 	while (s1[i])
// 	{
// 		str[j] = s1[i];
// 		j++;
// 		i++;
// 	}
// 	i = 0;
// 	while (s2[i])
// 	{
// 		str[j] = s2[i];
// 		j++;
// 		i++;
// 	}
// 	str[j] = 0;
// 	return (str);
// }

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*str;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
// 	if (!str)
// 		return (NULL);
// 	return (ft_join(s1, s2, str));
// }

// int	main(void)
// {
// 	int fd;
// 	char *line;
// 	char *buffer;

// 	buffer = get_next_line(0);
// 	while ((line = get_next_line(0)) != NULL)
// 	{
// 		buffer = ft_strjoin(buffer, line);
// 		free(line);
// 	}
// 	buffer = ft_strjoin(buffer, line);
// 	printf("%s\n", buffer);
// 	// free(buffer);
// 	return (0);
// }