/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:26:18 by mfusil            #+#    #+#             */
/*   Updated: 2023/02/17 15:56:12 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_home(char **tmp_env)
{
	int	i;

	i = 0;
	while (tmp_env[i] && ft_strncmp(tmp_env[i], "HOME=", 5))
		i++;
	if (tmp_env[i])
		chdir(&tmp_env[i][5]);
	else
		printf("error with HOME\n");
}

void	update_oldpwd(char **tmp_env, char *tmp_pwd)
{
	int	i;

	i = 0;
	while (tmp_env[i] && ft_strncmp(tmp_env[i], "OLDPWD=", 7))
		i++;
	if (tmp_env[i])
	{
		free(tmp_env[i]);
		tmp_env[i] = ft_strjoin("OLDPWD=", tmp_pwd);
		free(tmp_pwd);
	}
	else
		return ;
}

void	update_pwd(char **tmp_env)
{
	char	*update_pwd;
	int		i;

	i = 0;
	update_pwd = malloc(1024);
	getcwd(update_pwd, 1024);
	while (tmp_env[i] && ft_strncmp(tmp_env[i], "PWD=", 4) != 0)
		i++;
	if (tmp_env[i])
	{
		free(tmp_env[i]);
		tmp_env[i] = ft_strjoin("PWD=", update_pwd);
	}
	free(update_pwd);
}

char	*save_pwd(char **tmp_env)
{
	char	*save_pwd;
	int		i;

	i = 0;
	save_pwd = NULL;
	while (ft_strncmp(tmp_env[i], "PWD=", 4))
		i++;
	if (tmp_env[i])
		save_pwd = ft_strdup(&tmp_env[i][4]);
	return (save_pwd);
}

int	cd(t_var *shell, char **tmp_env)
{
	char	*path;

	path = NULL;
	path = save_pwd(tmp_env);
	if (!shell->flag && !shell->string)
		chdir(getenv("HOME"));
	else if (ft_strncmp(shell->string->content, "~", 1) == 0)
	{
		if (ft_strlen(shell->string->content) == 1)
			get_home(tmp_env);
		else
			path = cd_absolute_path(shell->string->content, path);
		if (path)
			update_oldpwd(tmp_env, path);
		update_pwd(tmp_env);
	}
	else if (ft_strcmp(shell->string->content, ".") == 0)
	{
		update_oldpwd(tmp_env, path);
		return (0);
	}
	else
		cd_2(shell, tmp_env, path);
	return (0);
}
