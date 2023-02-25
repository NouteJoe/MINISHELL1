/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuni-re <jmuni-re@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:42:56 by jmuni-re          #+#    #+#             */
/*   Updated: 2022/04/28 17:52:12 by jmuni-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*ft_realloc(char *line, char c, int *len)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *) malloc(*len + 2);
	if (!str)
		return (NULL);
	while (line && *len > i)
	{
		str[i] = line[i];
		i++;
	}
	str[*len] = c;
	*len = *len + 1;
	str[*len] = '\0';
	if (line)
		free(line);
	return (str);
}

char	*get_next_line(int fd)
{
	char	*line;
	char	c;
	int		len;

	len = 0;
	line = NULL;
	while (1)
	{
		if (read(fd, &c, 1) > 0)
			line = ft_realloc(line, c, &len);
		else
			c = '\0';
		if (c == '\n' || !c)
			return (line);
	}
	return (NULL);
}
/*
int	main (int argc, char **argv)
{
	int		fd;
	char	*str;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
		str = get_next_line(fd);
		printf("%s", str);
	}
	else
		return (1);
}
*/
