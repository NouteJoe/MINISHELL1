/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 19:25:32 by mfusil            #+#    #+#             */
/*   Updated: 2023/02/21 17:05:57 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env(char ***tmp_env)
{
	int	i;

	i = 0;
	while ((*tmp_env)[i])
	{
		ft_putstr((*tmp_env)[i]);
		printf("\n");
		i++;
	}
	g_exit_statut = 0;
	return (0);
}