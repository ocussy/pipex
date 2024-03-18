/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:35:20 by ocussy            #+#    #+#             */
/*   Updated: 2024/02/23 12:13:26 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*copy;
	int		i;

	i = 0;
	if (!src)
		return (NULL);
	copy = malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	while (src[i])
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
/*int	main(int argc, char *argv[])
{
	int	i;

	i = 0;

	while(++i < argc)
	{
		printf("%s\n",ft_strdup(argv[i]));
		printf("%s\n", strdup(argv[i]));
	}
	return (0);
}*/
