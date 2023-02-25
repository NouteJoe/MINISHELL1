/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuni-re <jmuni-re@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:48:25 by jmuni-re          #+#    #+#             */
/*   Updated: 2023/02/24 10:24:01 by jmuni-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_flag_cmd(t_var **shell, int i, char *cmd)
{
	int		start;
	t_list	*tmp;

	start = i;
	i = is_forbidden_char(i, cmd);
	tmp = ft_lstnew(ft_substr(cmd, start, i - start));
	ft_lstadd_back(&(*shell)->flag, tmp);
	return (i);
}

int	get_cmd(t_var **shell, int i, char *cmd)
{
	int	start;

	start = i;
	i = is_forbidden_char(i, cmd);
	(*shell)->cmd_arg = ft_substr(cmd, start, i - start);
	return (i);
}

void	get_space(t_var **tmp)
{
	char	*c;
	t_list	*space;

	c = ft_substr(" ", 0, 1);
	space = ft_lstnew(c);
	ft_lstadd_back(&(*tmp)->string, space);
}
