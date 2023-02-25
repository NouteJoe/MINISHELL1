/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:51:04 by mfusil            #+#    #+#             */
/*   Updated: 2023/02/24 10:52:48 by jmuni-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

void	init_struct(t_var **shell)
{
	(*shell)->save_input = dup(STDIN_FILENO);
	(*shell)->save_output = dup(STDOUT_FILENO);
	(*shell)->redir_input = NULL;
	(*shell)->redir_hdoc = NULL;
	(*shell)->redir_output = NULL;
	(*shell)->redir_append = NULL;
	(*shell)->infile = 0;
	(*shell)->outfile = 0;
	(*shell)->cmd_arg = NULL;
	(*shell)->flag = NULL;
	(*shell)->string = NULL;
	(*shell)->next = NULL;
}
