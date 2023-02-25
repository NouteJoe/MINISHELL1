/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuni-re <jmuni-re@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:10:24 by jmuni-re          #+#    #+#             */
/*   Updated: 2023/02/25 12:57:39 by jmuni-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_string_double(t_var **shell, int i, char *cmd, char **tmp_env)
{
	int		start;
	t_list	*tmp;

	i++;
	start = i;
	while (cmd[i] != '"')
	{
		if (cmd[i] == '$')
		{
			if ((*shell)->string && (*shell)->string->content)
				get_space(shell);
			tmp = ft_lstnew((char *)ft_substr(cmd, start, i - start));
			ft_lstadd_back(&(*shell)->string, tmp);
			i = get_variable(cmd, i, tmp_env, shell);
			start = i;
		}
		else
			i++;
	}
	tmp = ft_lstnew((char *)ft_substr(cmd, start, i - start));
	ft_lstadd_back(&(*shell)->string, tmp);
	i++;
	return (i);
}

int	get_string_simple(t_var **shell, int i, char *cmd)
{
	int		start;
	t_list	*tmp;

	i++;
	start = i;
	while (cmd[i] != '\'')
		i++;
	tmp = ft_lstnew((char *)ft_substr(cmd, start, i - start));
	ft_lstadd_back(&(*shell)->string, tmp);
	i++;
	return (i);
}

int	get_string(t_var **shell, int i, char *cmd, char **tmp_env)
{
	int		start;
	t_list	*tmp;

	start = i;
	while (cmd[i] && cmd[i] != '<' && cmd[i] != '>' && cmd[i] != '\''
		&& cmd[i] != '"' && cmd[i] != '|')
	{
		if (cmd[i] == ' ' && cmd[i + 1] == ' ')
		{
			tmp = ft_lstnew(ft_substr(cmd, start, i - start));
			ft_lstadd_back(&(*shell)->string, tmp);
			while (cmd[i] == ' ' && cmd[i + 1] == ' ')
				i++;
			start = i;
		}
		if (cmd[i] == '$')
		{
			tmp = ft_lstnew((char *)ft_substr(cmd, start, i - start));
			ft_lstadd_back(&(*shell)->string, tmp);
			i = get_variable(cmd, i, tmp_env, shell);
			start = i;
		}
		i++;
	}
	tmp = ft_lstnew(ft_substr(cmd, start, i - start));
	ft_lstadd_back(&(*shell)->string, tmp);
	return (i);
}
