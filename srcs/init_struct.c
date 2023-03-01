/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:51:04 by mfusil            #+#    #+#             */
/*   Updated: 2023/02/28 11:01:07 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

t_file	init_files(t_var **shell)
{
	t_file	files;

	files.outfiles = malloc(sizeof(int) * (ft_lstsize((*shell)->redir_output)
				+ ft_lstsize((*shell)->redir_append)));
	files.savein = dup(STDIN_FILENO);
	return (files);
}

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
