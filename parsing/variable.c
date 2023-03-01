/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuni-re <jmuni-re@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:39:20 by jmuni-re          #+#    #+#             */
/*   Updated: 2023/03/01 13:49:08 by jmuni-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_statut(t_var **shell, int i)
{
	t_list	*number;
	char	*str;

	str = malloc (sizeof(char) * 4);
	str = ft_itoa(g_exit_statut);
	if ((*shell)->cmd_arg == NULL)
		(*shell)->cmd_arg = str;
	else
	{
		number = ft_lstnew((char *)ft_substr(str, 0, 4));
		ft_lstadd_back(&(*shell)->string, number);
	}
	i++;
	return (i);
}

int	get_variable2(char *cmd, int i, char **tmp_env, t_var **shell)
{
	int		j;
	char	*str;
	int		size;

	j = 0;
	str = NULL;
	size = 0;
	size = is_forbidden_char(size, cmd);
	str = malloc(sizeof(char) * size + 1);
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '|' && cmd[i] != '"'
		&& cmd[i] != '\'' && cmd[i] != '$')
	{
		str[j] = cmd[i];
		i++;
		j++;
	}
	str[j] = '=';
	scan_tmp_env(tmp_env, str, j + 1, shell);
	free(str);
	return (i);
}

int	get_variable(char *cmd, int i, char **tmp_env, t_var **shell)
{
	i++;
	if (cmd[i] == '?')
		i = exit_statut(shell, i);
	else
		i = get_variable2(cmd, i, tmp_env, shell);
	return (i);
}

int	scan_tmp_env(char **tmp_env, char *str, int j, t_var **shell)
{
	t_list	*tmp;
	char	**tab;
	char	*tmp2;
	int		n;
	int		i;

	tmp = NULL;
	tab = NULL;
	n = 0;
	i = 0;
	while (tmp_env[n])
	{
		if (ft_strncmp(str, tmp_env[n], j) == 0)
		{
			tab = ft_split(tmp_env[n], '=');
			tmp2 = ft_strdup(tab[1]);
			tmp = ft_lstnew(tmp2);
			ft_lstadd_back(&(*shell)->string, tmp);
			while (tab[i++])
				free(tab[i]);
			free(tab);
		}
		n++;
	}
	return (0);
}
