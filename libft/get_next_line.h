/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocussy <ocussy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:12:28 by ocussy            #+#    #+#             */
/*   Updated: 2024/04/09 18:28:03 by ocussy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_make_join(char *line, char *buf);
char	*ft_make_line(int fd, char *line);
char	*ft_get_line(char *tempo);
char	*ft_clean(char *line);
char	*get_next_line(int fd);

#endif
