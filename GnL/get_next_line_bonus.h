/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuni-re <jmuni-re@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 18:20:21 by jmuni-re          #+#    #+#             */
/*   Updated: 2022/04/28 18:55:23 by jmuni-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef MAX_FD
#  define MAX_FD 256
# endif

char	*get_next_line(int fd);
char	*ft_realloc_cat(char *line, char c, int *len);

#endif
