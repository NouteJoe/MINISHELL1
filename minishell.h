/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:38:11 by mfusil            #+#    #+#             */
/*   Updated: 2023/02/25 13:14:51 by jmuni-re         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "GnL/get_next_line.h"
# include "Libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

int				g_exit_statut;

//----------------struct----------------//
typedef struct s_var
{
	int				fd_input;
	int				fd_output;
	int				save_input;
	int				save_output;

	int				nbr_pipe;
	int				pipe[2];

	t_list			*redir_input;
	t_list			*redir_hdoc;
	t_list			*redir_output;
	t_list			*redir_append;
	int				outfile;
	int				infile;

	char			*cmd_arg;
	t_list			*flag;
	t_list			*string;

	char			*path;

	struct s_var	*next;
}	t_var;

//----------------srcs----------------//
void	init_struct(t_var **shell);
char	**env_copy(char **envp);

//----------------parsing----------------//
int		check_cmd_user(t_var *tmp, char **tmp_env, char *cmd, int i);
int		check_cmd_user2(t_var *tmp, char **tmp_env, char *cmd, int i);
int		read_cmd_user(t_var **shell, char **tmp_env, char *cmd);

//----------------variable----------------//
int		exit_statut(t_var **shell, int i);
int		get_variable(char *cmd, int i, char **tmp_env, t_var **shell);
int		scan_tmp_env(char **tmp_env, char *str, int j, t_var **shell);

//----------------get_cmd----------------//
int		get_flag_cmd(t_var **shell, int i, char *cmd);
int		get_cmd(t_var **shell, int i, char *cmd);
void	get_space(t_var **tmp);

//----------------execution----------------//
void	exec(t_var **shell, char ***tmp_env);
void	redirection_hdoc(char *line);
void	handler_sig(int signum);
int		builtin_no_fork(t_var *shell, char ***tmp_env);
void	redirection_outfile(t_var **shell, int **files);
int		redirection_infile(t_var **shell);

//----------------structvar----------------//
void	ft_varadd_back(t_var **var, t_var *n);
t_var	*ft_varnew(void);

//----------------verification----------------//
int		is_double_quote(char *cmd);
int		is_simple_quote(char *cmd);
int		is_forbidden_char(int i, char *cmd);
int		is_forbidden_char2(int i, char *cmd);

//----------------redir----------------//
int		here_doc(t_var **shell, int i, char *cmd);
int		input_file(t_var **shell, int i, char *cmd);
int		output_file(t_var **shell, int i, char *cmd);
int		append(t_var **shell, int i, char *cmd);

//----------------string----------------//
int		get_string_double(t_var **shell, int i, char *cmd, char **tmp_env);
int		get_string_simple(t_var **shell, int i, char *cmd);
int		get_string(t_var **shell, int i, char *cmd, char **tmp_env);

//----------------builtins----------------//
int		pwd(char **tmp_env);
int		env(char ***tmp_env);
int		echo(t_var *shell);
int		export(t_var *shell, char ***tmp_env);
int		lexit(t_var *shell);
int		unset(t_var *shell, char ***envp);

//----------------cd----------------//
int		cd(t_var *shell, char **tmp_env);
int		cd_2(t_var *shell, char **tmp_env, char *tmp_pwd);
void	update_pwd(char **tmp_env);
void	update_oldpwd(char **tmp_env, char *tmp_pwd);
char	*save_pwd(char **tmp_env);
void	get_home(char **tmp_env);
char	*create_new_pwd(char *tmp_pwd, char *string);
char	*cd_absolute_path(char *string, char *path);

//----------------utils----------------//
char	*ft_find_path(char **env, char *cmd);

#endif
