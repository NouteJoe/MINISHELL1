/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuni-re <jmuni-re@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:04:07 by jmuni-re          #+#    #+#             */
/*   Updated: 2023/02/26 11:21:47 by jmuni-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_cmd_user(t_var *tmp, char **tmp_env, char *cmd, int i)
{
	while (cmd[i] == ' ')
		i++;
	if (ft_strncmp(&cmd[i], "<<", 2) == 0)
		i = here_doc(&tmp, i, cmd);
	else if (cmd[i] == '<')
		i = input_file(&tmp, i, cmd);
	else if (ft_strncmp(&cmd[i], ">>", 2) == 0)
		i = append(&tmp, i, cmd);
	else if (cmd[i] == '>')
		i = output_file(&tmp, i, cmd);
	else if (cmd[i] == '$')
		i = get_variable(cmd, i, tmp_env, &tmp);
	else if (cmd[i] != ' ' && !tmp->cmd_arg)
		i = get_cmd(&tmp, i, cmd);
	else if (cmd && cmd[i] == '-' && cmd[i - 1] == ' ')
		i = get_flag_cmd(&tmp, i, cmd);
	else if (cmd[i] == '\"')
		i = get_string_double(&tmp, i, cmd, tmp_env);
	else if (cmd[i] == '\'')
		i = get_string_simple(&tmp, i, cmd);
	else
		return (i);
	return (i);
}

int	new_shell(t_var **tmp, t_var **shell, int i)
{
	ft_varadd_back(shell, *tmp);
	*tmp = ft_varnew();
	i++;
	return (i);
}

int	read_cmd_user(t_var **shell, char **tmp_env, char *cmd)
{
	int		i;
	t_var	*tmp;
	int		start;

	tmp = ft_varnew();
	i = 0;
	if (is_double_quote(cmd) % 2 != 0 || is_simple_quote(cmd) % 2 != 0)
		return (1);
	while (cmd && cmd[i])
	{
		start = i;
		i = check_cmd_user(tmp, tmp_env, cmd, i);
		if (i == start)
		{
			if (cmd[i] == '|')
				i = new_shell(&tmp, shell, i);
			else
				i = get_string(&tmp, i, cmd, tmp_env);
		}
		if (cmd[i] == ' ' && tmp->string && tmp->string->content)
			get_space(&tmp);
	}
	ft_varadd_back(shell, tmp);
	return (0);
}
