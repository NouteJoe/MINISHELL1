/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verification.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuni-re <jmuni-re@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:17:35 by jmuni-re          #+#    #+#             */
/*   Updated: 2023/02/24 10:27:07 by jmuni-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_double_quote(char *cmd)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (cmd[i])
	{
		if (cmd[i] == '"')
			nb++;
		i++;
	}
	return (nb);
}

int	is_simple_quote(char *cmd)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
			nb++;
		i++;
	}
	return (nb);
}

int	is_forbidden_char2(int i, char *cmd)
{
	while (cmd[i] && cmd[i] == ' ' && cmd[i] != '<' && cmd[i] != '>'
		&& cmd[i] != '|')
		i++;
	if (cmd[i] == '>' || cmd[i] == '<')
	{
		printf("zsh: parse error near `%c'\n", (cmd[i]));
		g_exit_statut = 1;
		i = ft_strlen(cmd);
	}
	return (i);
}

int	is_forbidden_char(int i, char *cmd)
{
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '<' && cmd[i] != '>'
		&& cmd[i] != '|')
	{
		if (cmd[i] == '$')
		{
			printf("No variable file please\n");
			i = ft_strlen(cmd);
		}
		i++;
	}
	return (i);
}
