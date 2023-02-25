/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:28:30 by mfusil            #+#    #+#             */
/*   Updated: 2023/02/23 16:46:07 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// TODO cat
// TODO redirection
// buildin

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
		tmp[i] = shell->flag->content;
		shell->flag = shell->flag->next;
		i++;
	}
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

int process(t_var *shell, char **tmp_env, int tmp, int *outfiles, int infiles) {
  pid_t pid;
  int status;
  status = 0;
  pipe(shell->pipe);
  // TODO process open file and redirection
  pid = fork();
  if (pid == 0) {
	if (shell->redir_input) {
	  dup2(infiles, STDIN_FILENO);
	} else
	  dup2(tmp, STDIN_FILENO);
	if (shell->next && shell->redir_output) {
	  dup2(outfiles[0], STDOUT_FILENO);
	} else if (shell->next) {
	  dup2(shell->pipe[1], STDOUT_FILENO);
	}
	close(shell->pipe[0]);
	builtin_fork(shell, tmp_env);
	exit(1);
  } else {
	dup2(shell->pipe[0], tmp);
	close(shell->pipe[1]);
	wait(NULL);
  }
  return (status);
}

void redirout(int *outfiles, t_var *shell) {
  char *str;
  int i = 1;
  int outfile;
  int flag = 0;
  int tmp = outfiles[0];
  close(outfiles[0]);
  if (shell->redir_output) {
	outfile = open((shell)->redir_output->content, O_RDONLY);
	if (outfile == tmp)
	  flag = 1;
  }
  if (shell->redir_output && flag != 1) {
	outfile = open((shell)->redir_output->content, O_RDONLY);
  }

  str = get_next_line(outfile);
  while (str) {
	while (i != ft_lstsize((shell)->redir_output) +
					ft_lstsize((shell)->redir_append)) {
	  write(outfiles[i], str, ft_strlen(str));
	  i++;
	}
	str = get_next_line(outfile);
	i = 1;
  }
}

void	exec(t_var **shell, char ***tmp_env)
{
	int		i;
	int		infiles;
	int		*outfiles;
	t_var	*tmp2;

	i = 0;
	tmp2 = *shell;
	(*shell)->save_input = dup(STDIN_FILENO);
	outfiles = malloc(sizeof(int) * (ft_lstsize((*shell)->redir_output)
				+ ft_lstsize((*shell)->redir_append)));
	if (!builtin_no_fork(*shell, tmp_env))
		return ;
	else
	{
		while (tmp2)
		{
			if ((tmp2)->redir_input)
			{
				while ((tmp2)->redir_input)
				{
					infiles = redirection_infile(&tmp2);
					if (tmp2->redir_output || tmp2->redir_append)
					{
						(*shell)->save_output = dup(STDOUT_FILENO);
						close(STDOUT_FILENO);
						redirection_outfile(&tmp2, &outfiles);
						dup2(outfiles[0], STDOUT_FILENO);
					}
					process(tmp2, *tmp_env, (*shell)->save_input, outfiles, infiles);
					close(infiles);
					if (tmp2->redir_output || tmp2->redir_append)
						redirout(outfiles, tmp2);
					while (i != ft_lstsize((tmp2)->redir_output)
						+ ft_lstsize((tmp2)->redir_append))
					{
						close(outfiles[i]);
						i++;
					}
					if (tmp2->redir_output || tmp2->redir_append)
						dup2((*shell)->save_output, STDOUT_FILENO);
					(tmp2)->redir_input = (tmp2)->redir_input->next;
				}
			}
			else if ((tmp2)->redir_hdoc)
			{
				if (tmp2->redir_output || tmp2->redir_append)
				{
					(*shell)->save_output = dup(STDOUT_FILENO);
					close(STDOUT_FILENO);
					redirection_outfile(&tmp2, &outfiles);
					dup2(outfiles[0], STDOUT_FILENO);
				}
				redirection_hdoc(tmp2->redir_hdoc->content);
				while (i != ft_lstsize((tmp2)->redir_output)
					+ ft_lstsize((tmp2)->redir_append))
				{
					close(outfiles[i]);
					i++;
				}
				if (tmp2->redir_output || tmp2->redir_append)
					dup2((*shell)->save_output, STDOUT_FILENO);
				process(tmp2, *tmp_env, (*shell)->save_input, outfiles, infiles);
			}
			else if ((tmp2->redir_output || tmp2->redir_append)
				&& !tmp2->redir_input)
			{
				(*shell)->save_output = dup(STDOUT_FILENO);
				close(STDOUT_FILENO);
				redirection_outfile(&tmp2, &outfiles);
				dup2(outfiles[0], STDOUT_FILENO);
				process(tmp2, *tmp_env, (*shell)->save_input, outfiles, infiles);
				redirout(outfiles, tmp2);
				while (i != ft_lstsize((tmp2)->redir_output)
					+ ft_lstsize((tmp2)->redir_append))
				{
					close(outfiles[i]);
					i++;
				}
				dup2((*shell)->save_output, STDOUT_FILENO);
			}
			else
				process(tmp2, *tmp_env, (*shell)->save_input, outfiles, infiles);
			tmp2 = tmp2->next;
		}
	}
}
