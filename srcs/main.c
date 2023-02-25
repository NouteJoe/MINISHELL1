/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:37:40 by mfusil            #+#    #+#             */
/*   Updated: 2023/02/21 17:05:37 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>

void	free_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->content);
		free(tmp);
	}
}

void	clean_shell(t_var **shell)
{
	t_var	*tmp;

	while (*shell)
	{
		tmp = *shell;
		*shell = (*shell)->next;
		free_list((tmp)->redir_input);
		free_list((tmp)->redir_output);
		free_list((tmp)->redir_append);
		free_list((tmp)->redir_hdoc);
		free_list((tmp)->flag);
		free_list((tmp)->string);
		free(tmp->cmd_arg);
		free(tmp);
	}
}

int	nbr_of_cmd(char *input)
{
	int	i;
	int	nbr_cmd;

	i = 0;
	nbr_cmd = 0;
	while (input[i])
	{
		if (input[i] == '|')
			nbr_cmd++;
		i++;
	}
	return (nbr_cmd);
}

int	main(int argc, char **argv, char **envp)
{
	t_var	*shell;
	char	**tmp_env;
	char	*cmd;

	(void)argv;
	if (argc != 1)
		return (write(1, "too many arguments\n", 19));
	shell = NULL;
	tmp_env = env_copy(envp);
	signal(SIGINT, handler_sig);
	signal(SIGQUIT, handler_sig);
	while (1)
	{
		cmd = readline("minishell> ");
		if (cmd == NULL)
			exit(0);
		if (cmd)
			add_history(cmd);
		if (read_cmd_user(&shell, tmp_env, cmd) == 0)
			exec(&shell, &tmp_env);
		if (shell)
			clean_shell(&shell);
		free(cmd);
	}
	return (0);
}
