/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:07:20 by mfusil            #+#    #+#             */
/*   Updated: 2023/02/21 15:53:16 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(char **tmp_env)
{
	char	*path_pwd;
	int		i;

	path_pwd = NULL;
	i = 0;
	while (tmp_env[i] && path_pwd == NULL)
	{
		if (ft_strncmp(tmp_env[i], "PWD", 3) == 0)
			path_pwd = &tmp_env[i][4];
		i++;
	}
	printf("%s\n", path_pwd);
	return (0);
}
