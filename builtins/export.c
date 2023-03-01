/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:07:21 by mfusil            #+#    #+#             */
/*   Updated: 2023/02/27 14:12:12 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**new_env(t_var *shell, char ***tmp_env)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = malloc((ft_strlen_tab(*tmp_env) + 2) * sizeof(char *));
	while ((*tmp_env)[i])
	{
		tmp[i] = ft_strdup((*tmp_env)[i]);
		free((*tmp_env)[i]);
		i++;
	}
	tmp[i] = ft_strdup(shell->string->content);
	i++;
	tmp[i] = NULL;
	free(*tmp_env);
	return (tmp);
}

int	var_in_env(char **tmp_env, char *string)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (string[len] != '=')
		len++;
	while (tmp_env[i])
	{
		if (ft_strncmp(tmp_env[i], string, len) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	change_variable_in_env(char **tmp_env, char *string)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (string[len] != '=')
		len++;
	while (tmp_env[i])
	{
		if (!ft_strncmp(tmp_env[i], string, len + 1))
		{
			free(tmp_env[i]);
			tmp_env[i] = ft_strdup(string);
		}
		i++;
	}
}

int	verif_export(t_var *shell)
{
	int	i;

	if (ft_strcmp(shell->string->content, "=") == 0)
		return (1);
	if (shell->string->content[0] >= '0' && shell->string->content[0] <= '9')
		return (1);
	i = 0;
	while (shell->string->content[i])
	{
		if (shell->string->content[i] == '=' && (shell->string->content[i - 1]
				== ' ' || shell->string->content[i + 1] == ' '))
			return (1);
		i++;
	}
	return (0);
}

int	export(t_var *shell, char ***tmp_env)
{
	g_exit_statut = 0;
	if (verif_export(shell))
	{
		g_exit_statut = 1;
		return (printf("error with export\n"));
	}
	if (shell->string->content == NULL)
	{
		g_exit_statut = 1;
		return (printf("no argument with export\n"));
	}
	if (shell->string->content)
	{
		if (var_in_env(*tmp_env, shell->string->content) == 0)
			change_variable_in_env(*tmp_env, shell->string->content);
		else
			(*tmp_env) = new_env(shell, tmp_env);
	}
	return (0);
}
