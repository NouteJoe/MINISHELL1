/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:28:30 by mfusil            #+#    #+#             */
/*   Updated: 2023/03/01 11:44:07 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_create_tab(t_var *shell)
{
	char	**tmp;
	int		i;
	t_list	*flag;

	flag = shell->flag;
	i = 0;
	while (flag)
	{
		flag = flag->next;
		i++;
	}
	tmp = malloc(sizeof(char *) * i + 2);
	tmp[0] = shell->cmd_arg;
	i = 1;
	while (shell->flag)
	{
		tmp[i++] = shell->flag->content;
		shell->flag = shell->flag->next;
	}
	if (shell->string)
		tmp[i++] = shell->string->content;
	tmp[i] = NULL;
	return (tmp);
}

int	builtin_fork(t_var *shell, char **tmp_env)
{
	if (ft_strcmp(shell->cmd_arg, "echo") == 0)
		return (echo(shell));
	else if (ft_strcmp(shell->cmd_arg, "pwd") == 0)
		return (pwd(tmp_env));
	else
	{
		if (execve(ft_find_path(tmp_env, shell->cmd_arg), ft_create_tab(shell),
				tmp_env) == -1)
			printf("cmd don't exist\n");
	}
	return (1);
}

void	parent_process(t_var *shell, int tmp)
{
	dup2(shell->pipe[0], tmp);
	close(shell->pipe[1]);
	wait(NULL);
}

int	process(t_var *shell, char **tmp_env, t_file files)
{
	pid_t	pid;
	int		status;

	status = 0;
	pipe(shell->pipe);
	pid = fork();
	if (pid == 0)
	{
		if (shell->redir_input)
			dup2(files.infiles, STDIN_FILENO);
		else
			dup2(files.savein, STDIN_FILENO);
		if (shell->next && shell->redir_output)
			dup2(files.outfiles[0], STDOUT_FILENO);
		else if (shell->next)
			dup2(shell->pipe[1], STDOUT_FILENO);
		close(shell->pipe[0]);
		builtin_fork(shell, tmp_env);
		exit(1);
	}
	else
		parent_process(shell, files.savein);
	return (status);
}

void	exec(t_var **shell, char ***tmp_env)
{
	t_var	*tmp2;
	t_file	files;

	files = init_files(shell);
	tmp2 = *shell;
	if (!builtin_no_fork(*shell, tmp_env))
		return ;
	else
	{
		while (tmp2)
		{
			if ((tmp2)->redir_input)
				while ((tmp2)->redir_input)
					if (infiles(&tmp2, &files, tmp_env))
						return ;
			if ((tmp2)->redir_hdoc)
				heredoc(tmp2, &files, tmp_env);
			else if ((tmp2->redir_output || tmp2->redir_append)
				&& !tmp2->redir_input)
				outfile(&tmp2, &files, tmp_env);
			else
				process(tmp2, *tmp_env, files);
			tmp2 = tmp2->next;
		}
	}
}
