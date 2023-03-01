/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:45:04 by mfusil            #+#    #+#             */
/*   Updated: 2023/03/01 11:32:47 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	outfile(t_var **tmp2, t_file *files, char ***tmp_env)
{
	files->i = 0;
	files->saveout = dup(STDOUT_FILENO);
	close(STDOUT_FILENO);
	redirection_outfile(tmp2, &files->outfiles);
	dup2(files->outfiles[0], STDOUT_FILENO);
	process(*tmp2, *tmp_env, *files);
	redirout(files->outfiles, *tmp2);
	while (files->i != ft_lstsize((*tmp2)->redir_output)
		+ ft_lstsize((*tmp2)->redir_append))
	{
		close(files->outfiles[files->i]);
		files->i++;
	}
	dup2(files->saveout, STDOUT_FILENO);
}

void	heredoc(t_var *tmp2, t_file *files, char ***tmp_env)
{
	files->i = 0;
	if (tmp2->redir_output || tmp2->redir_append)
	{
		files->saveout = dup(STDOUT_FILENO);
		close(STDOUT_FILENO);
		redirection_outfile(&tmp2, &files->outfiles);
		dup2(files->outfiles[0], STDOUT_FILENO);
	}
	redirection_hdoc(tmp2->redir_hdoc->content);
	while (files->i != ft_lstsize((tmp2)->redir_output)
		+ ft_lstsize((tmp2)->redir_append))
	{
		close(files->outfiles[files->i]);
		files->i++;
	}
	if (tmp2->redir_output || tmp2->redir_append)
		dup2(files->saveout, STDOUT_FILENO);
	process(tmp2, *tmp_env, *files);
}

int	infiles(t_var **tmp2, t_file *files, char ***tmp_env)
{
	files->i = 0;
	files->infiles = redirection_infile(tmp2);
	if (files->infiles == -1)
		return (1);
	if ((*tmp2)->redir_output || (*tmp2)->redir_append)
	{
		files->saveout = dup(STDOUT_FILENO);
		close(STDOUT_FILENO);
		redirection_outfile(tmp2, &files->outfiles);
		dup2(files->outfiles[0], STDOUT_FILENO);
	}
	process(*tmp2, *tmp_env, *files);
	close(files->infiles);
	if ((*tmp2)->redir_output || (*tmp2)->redir_append)
		redirout(files->outfiles, *tmp2);
	while (files->i != ft_lstsize((*tmp2)->redir_output)
		+ ft_lstsize((*tmp2)->redir_append))
	{
		close(files->outfiles[files->i]);
		files->i++;
	}
	if ((*tmp2)->redir_output || (*tmp2)->redir_append)
		dup2(files->saveout, STDOUT_FILENO);
	(*tmp2)->redir_input = (*tmp2)->redir_input->next;
	return (0);
}
