/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:36:29 by mfusil            #+#    #+#             */
/*   Updated: 2023/02/23 16:46:29 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verif_unset(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if ((ft_isalnum(string[i]) == 0) && string[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

char	**new_envp(char **envp, char *string)
{
	char	**tab;
	char	**tmp;
	int		i;
	int		j;

	i = -1;
	j = 0;
	tab = malloc ((ft_strlen_tab(envp)) * sizeof(char *));
	while (envp[++i])
	{
		tmp = ft_split(envp[i], '=');
		if (ft_strcmp(tmp[0], string))
		{
			tab[j] = ft_strdup(envp[i]);
			j++;
		}
		ft_free_tab(tmp);
	}
	i--;
	tab[i] = NULL;
	return (tab);
}

int	unset(t_var *shell, char ***envp)
{
	char	**tab;
	int		i;

	i = 0;
	g_exit_statut = 0;
	if (shell->string->content == NULL)
		return (0);
	if (ft_isdigit(shell->string->content[0]))
		return (0);
	if (verif_unset(shell->string->content))
		return (0);
	tab = new_envp(*envp, shell->string->content);
	*envp = tab;
	return (0);
}
