/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:01:24 by mfusil            #+#    #+#             */
/*   Updated: 2023/02/23 16:56:11 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo(t_var *shell)
{
	while (shell->string)
	{
		printf("%s", shell->string->content);
		shell->string = shell->string->next;
	}
	//if (ft_strcmp(shell->flag->content, "-n") != 0)
		printf("\n");
	return (0);
}
