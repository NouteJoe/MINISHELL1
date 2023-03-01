/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirout.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:17:27 by mfusil            #+#    #+#             */
/*   Updated: 2023/02/28 11:03:44 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_in_outfile(t_var *shell, char *str, int *outfiles, int outfile)
{
	int	i;

	i = 1;
	while (str)
	{
		while (i != ft_lstsize((shell)->redir_output)
			+ ft_lstsize((shell)->redir_append))
		{
			write(outfiles[i], str, ft_strlen(str));
			i++;
		}
		str = get_next_line(outfile);
		i = 1;
	}
}

void	redirout(int *outfiles, t_var *shell)
{
	char	*str;
	int		i;
	int		outfile;
	int		flag;
	int		tmp;

	i = 1;
	flag = 0;
	tmp = outfiles[0];
	close(outfiles[0]);
	if (shell->redir_output)
	{
		outfile = open((shell)->redir_output->content, O_RDONLY);
		if (outfile == tmp)
			flag = 1;
	}
	if (shell->redir_output && flag != 1)
		outfile = open((shell)->redir_output->content, O_RDONLY);
	str = get_next_line(outfile);
	write_in_outfile(shell, str, outfiles, outfile);
}
