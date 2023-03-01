/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:13:08 by mfusil            #+#    #+#             */
/*   Updated: 2023/03/01 11:37:35 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirection_hdoc(char *line)
{
	char	*str;
	int		size;
	int		fd;

	fd = open(line, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	size = ft_strlen(line);
	while (42)
	{
		signal(SIGINT, handler_sig);
		signal(SIGQUIT, handler_sig);
		str = readline("> ");
		if (!str || (!ft_strncmp(line, str, size)))
		{
			close(fd);
			free(str);
			break ;
		}
		ft_putendl_fd(str, fd, 0);
		free(str);
	}
	close(fd);
}

int	redirection_infile(t_var **shell)
{
	int	fd;

	fd = open((*shell)->redir_input->content, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("error infile\n", 2);
		return (-1);
	}
	return (fd);
}

void	redir_output_2(t_var **shell, char **str)
{
	if ((*shell)->redir_output && (*shell)->redir_output->content)
	{
		*str = malloc(sizeof(char) * (ft_strlen
					((*shell)->redir_output->content) + 1));
		ft_strlcpy(*str, (*shell)->redir_output->content,
			ft_strlen((*shell)->redir_output->content) + 1);
	}
	else
	{
		*str = malloc(sizeof(char) * (ft_strlen
					((*shell)->redir_append->content) + 1));
		ft_strlcpy(*str, (*shell)->redir_append->content,
			ft_strlen((*shell)->redir_append->content) + 1);
	}
}

int	redir_output_1(t_var tmp2, int **files)
{
	int		i;
	int		fd;

	i = 0;
	while ((tmp2).redir_output)
	{
		fd = open((tmp2).redir_output->content,
				O_WRONLY | O_TRUNC | O_CREAT, 0664);
		if (verif_fd(fd))
			return (1);
		(*files)[i++] = fd;
		tmp2.redir_output = tmp2.redir_output->next;
	}
	while ((tmp2).redir_append)
	{
		fd = open((tmp2).redir_append->content,
				O_CREAT | O_WRONLY | O_APPEND, 0664);
		if (verif_fd(fd))
			return (1);
		(*files)[i++] = fd;
		tmp2.redir_append = tmp2.redir_append->next;
	}
	return (0);
}

void	redirection_outfile(t_var **shell, int **files)
{
	t_var	tmp2;
	t_list	*tmp;
	char	*str;

	str = NULL;
	tmp2 = **shell;
	if (redir_output_1(tmp2, files))
		return ;
	redir_output_2(shell, &str);
	tmp = ft_lstnew(str);
	if ((*shell)->next)
		ft_lstadd_back(&(*shell)->next->redir_input, tmp);
}
