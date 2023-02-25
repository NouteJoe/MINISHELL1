/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:08:49 by mfusil            #+#    #+#             */
/*   Updated: 2023/02/21 16:11:19 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*cd_absolute_path(char *string, char *path)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_split(string, '/');
	string = ft_strjoin(getenv("HOME"), "/");
	while (tab[++i])
	{
		string = ft_strjoin(string, tab[i]);
		string = ft_strjoin(string, "/");
	}
	if (chdir(string) == -1)
		printf("cd: no such file or directory\n");
	else
		return (string);
	return (path);
}

void	change_directory(char **tmp_env)
{
	int	x;
	int	y;
	int	z;

	x = 0;
	y = 0;
	z = 0;
	while (tmp_env[x] && ft_strncmp(tmp_env[x], "HOME=", 5))
		x++;
	while (tmp_env[y] && ft_strncmp(tmp_env[y], "PWD=", 4))
		y++;
	if (tmp_env[x] && tmp_env[y])
	{
		if (ft_strcmp(&tmp_env[x][4], &tmp_env[y][3]) == 0)
			return ;
		else
		{
			while (tmp_env[y][z])
				z++;
			while (tmp_env[y][z] != '/')
				z--;
			tmp_env[y][z + 1] = 0;
			chdir(&tmp_env[y][4]);
		}
	}
}

char	*create_new_pwd(char *tmp_pwd, char *string)
{
	char	*tmp;
	char	*new_pwd;

	tmp = ft_strjoin(tmp_pwd, "/");
	new_pwd = ft_strjoin(tmp, string);
	free(tmp);
	return (new_pwd);
}

int	cd_2(t_var *shell, char **tmp_env, char *tmp_pwd)
{
	char	*path;

	path = NULL;
	if (ft_strcmp(shell->string->content, "..") == 0)
	{
		change_directory(tmp_env);
		if (tmp_pwd)
			update_oldpwd(tmp_env, tmp_pwd);
		update_pwd(tmp_env);
	}
	else if (shell->string->content)
	{
		path = create_new_pwd(tmp_pwd, shell->string->content);
		if (chdir(path) == -1)
		{
			printf("error cd\n");
			g_exit_statut = 1;
		}
		if (tmp_pwd)
			update_oldpwd(tmp_env, path);
		update_pwd(tmp_env);
	}
	return (0);
}
