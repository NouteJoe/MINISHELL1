/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuni-re <jmuni-re@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:10:24 by jmuni-re          #+#    #+#             */
/*   Updated: 2023/02/26 10:38:18 by jmuni-re         ###   ########.fr       */
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

void	add_back_list(t_var **shell, char *cmd, int i, int start)
{
	t_list	*tmp;

	tmp = ft_lstnew(ft_substr(cmd, start, i - start));
	ft_lstadd_back(&(*shell)->string, tmp);
}

int	get_string(t_var **shell, int i, char *cmd, char **tmp_env)
{
	int		start;

	start = i;
	while (cmd[i] && cmd[i] != '<' && cmd[i] != '>' && cmd[i] != '\''
		&& cmd[i] != '"' && cmd[i] != '|')
	{
		if (cmd[i] == ' ' && cmd[i + 1] == ' ')
		{
			add_back_list(shell, cmd, i, start);
			while (cmd[i] == ' ' && cmd[i + 1] == ' ')
				i++;
			start = i;
		}
		if (cmd[i] == '$')
		{
			add_back_list(shell, cmd, i, start);
			i = get_variable(cmd, i, tmp_env, shell);
			start = i;
		}
		i++;
	}
	add_back_list(shell, cmd, i, start);
	return (i);
}
