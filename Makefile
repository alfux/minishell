# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/31 19:02:34 by alfux             #+#    #+#              #
#    Updated: 2022/08/01 01:30:57 by alfux            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SPATH	= src/

SRC		= main.c

OPATH	= obj/

OBJ		= $(SRC:%.c=$(OPATH)%.o)

LPATH	= libft/

LIBFT	= libft.a

HPATH	= hdr/

HEADER	= minishell.h

OPTION	= -Wall -Werror -Wextra -I$(LPATH) -I$(HPATH)

SIL		= --no-print-directory

NAME	= minishell

all					:	$(NAME)

$(NAME)				:	$(OPATH) $(OBJ) $(LPATH)$(LIBFT)
						@(gcc $(OPTION) $(OBJ) $(LPATH)$(LIBFT) -lreadline -o $@)
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

clean				:
						@(cd $(LPATH) && $(MAKE) $(SIL) clean)
						@(rm -rf $(OPATH))
						@(echo "\033[31mcleaned object files\033[0m")

fclean				:	clean
						@(cd $(LPATH) && $(MAKE) $(SIL) fclean)
						@(rm $(NAME))
						@(echo "\033[31m$(NAME) removed\033[0m")

re					:	fclean all

.PHONY				:	all clean fclean re
