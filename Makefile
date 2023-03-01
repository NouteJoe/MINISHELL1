# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/20 18:45:16 by mfusil            #+#    #+#              #
#    Updated: 2023/02/28 10:46:19 by mfusil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = Libft/libft.a

LDFLAGS = -L/goinfre/$(USER)/.brew/Cellar/readline/8.2.1/lib/
CPPFLAGS = -I/goinfre/$(USER)/.brew/Cellar/readline/8.2.1/include
CFLAG = -g -Wall -Wextra -Werror 
	
SRCS =	srcs/main.c\
		srcs/init_struct.c\
		srcs/env_copy.c

PARSING = parsing/parsing.c\
		parsing/redir.c\
		parsing/path.c\
		parsing/verification.c\
		parsing/string.c\
		parsing/get_cmd.c\
		parsing/variable.c

EXEC = exec/exec.c\
	   exec/signal.c\
	   exec/redirect.c\
	   exec/builtin_no_fork.c\
	   exec/verif_fd.c\
	   exec/redirout.c\
	   exec/exec2.c

BUILTINS = builtins/pwd.c\
		   builtins/env.c\
		   builtins/echo.c\
		   builtins/cd.c\
		   builtins/cd2.c\
		   builtins/export.c\
		   builtins/exit.c\
		   builtins/unset.c

GNL = GnL/get_next_line.c

STRUCT = structvar/ft_addback.c\
		structvar/ft_varnew.c

ALL_SRCS = $(SRCS)\
		   $(PARSING)\
		   $(EXEC)\
		   $(BUILTINS)\
		   $(UTILS)\
		   $(STRUCT)\
		   $(GNL) 


OBJS = $(ALL_SRCS:.c=.o)

RE_LIBFT = @make -C Libft

all : $(NAME)

alln : all
		norminette

.c.o:
	gcc  $(CFLAG) -o $@ -c $< $(CPPFLAGS) 

$(NAME) : $(OBJS)
		$(RE_LIBFT)
		gcc $(CFLAG) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS) $(CPPFLAGS)  -lreadline
		@echo "$(GREEN)$(BOLD)Minishell Executable Created"

clean :
		@rm -rf $(OBJS)
		@make clean -C Libft
		@echo "$(GREEN)$(BOLD)Minishell objects removed"

fclean : clean
		@rm -rf $(NAME)
		@make fclean -C Libft
		@echo "$(GREEN)$(BOLD)Executable removed"

re : fclean all

#----------------------COLORS----------------------
GREEN=\x1b[32m
BOLD=\033[1m

.PHONY: all clean fclean re