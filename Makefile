# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/31 19:02:34 by alfux             #+#    #+#              #
#    Updated: 2022/08/31 02:16:17 by alfux            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SPATH	=	src/

SRC		=	main.c ft_prompt.c ft_cd.c ft_strtdup.c ft_sfree.c ft_env.c	\
			ft_newpwd.c ft_errmsg.c ft_free.c ft_echo.c ft_cmdspl.c		\
			ft_root_parse.c ft_pwd.c ft_exit.c ft_isbuiltin.c			\
			ft_execute.c ft_setvar.c ft_strtcat.c ft_strtlen.c			\
			ft_isvarin.c ft_export.c ft_unset.c	ft_strtdelone.c			\
			ft_addhis.c ft_savhis.c ft_errno.c ft_gethis.c ft_isntvar.c	\
			ft_isextern.c												\

OPATH	=	obj/

OBJ		=	$(SRC:%.c=$(OPATH)%.o)

LPATH	=	libft/

LIBFT	=	libft.a

HPATH	=	hdr/

RIPATH	=	/opt/homebrew/opt/readline/include

RLPATH	=	/opt/homebrew/opt/readline/lib

HEADER	=	minishell.h

OPTION	=	-Wall -Werror -Wextra -I$(LPATH) -I$(HPATH) -I$(RIPATH) -g

SIL		=	--no-print-directory

NAME	=	minishell

HISTORY	=	.$(NAME)_history

LEAKS	=	chleaks

$(NAME)				:	$(OPATH) $(OBJ) $(LPATH)$(LIBFT)
						@(gcc $(OPTION) $(OBJ) $(LPATH)$(LIBFT) -o			\
						$@ -L$(RLPATH) -lreadline)
						@(echo "\033[32m$@ linked\033[0m")

$(OPATH)%.o			:	$(SPATH)%.c $(HPATH)$(HEADER)
						@(gcc $(OPTION) -c $< -o $@)
						@(echo "\033[90m$@ compiled\033[0m")

$(OPATH)			:
						@(mkdir $@)
						@(echo "\033[90m$@ directory created\033[0m")

$(LPATH)$(LIBFT)	:
						@(cd $(LPATH) && $(MAKE) $(SIL) bonus clean)
						@(echo "\033[90m$(LIBFT) compiled\033[0m")

all					:	$(NAME) $(LEAKS)

clean				:
						@(cd $(LPATH) && $(MAKE) $(SIL) clean)
						@(rm -rf $(OPATH))
						@(echo "\033[31mobject files removed\033[0m")

cclean				:
						@(rm -rf $(LEAKS))
						@(echo "\033[31m$(LEAKS) removed\033[0m")

fclean				:	clean cclean
						@(cd $(LPATH) && $(MAKE) $(SIL) fclean)
						@(rm -rf $(NAME) $(HISTORY))
						@(echo "\033[31m$(NAME) removed\033[0m")

re					:	fclean all

$(LEAKS)				:
						@(echo "export MallocStackLogging=1\nleaks --atExit"\
						"-- ./$(NAME)\nunset MallocStackLogging" > $(LEAKS))
						@(chmod 755 $(LEAKS))
						@(echo "\033[32m$(LEAKS) written\033[0m")

leaks				:	$(LEAKS)

.PHONY				:	all clean fclean re cclean
