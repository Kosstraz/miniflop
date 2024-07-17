# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bama <bama@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 16:21:19 by ymanchon          #+#    #+#              #
#    Updated: 2024/07/18 00:22:48 by bama             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ################ #
#*    COULEURS    *#
# ################ #

CLASSIC	=	\e[0m
RED_B	=	\e[1;31m
GREEN_B	=	\e[1;32m
YELLO	=	\e[33m

# ############### #
#*   VARIABLES   *#
# ############### #

NAME = minishell

CC =	cc

SRCS =	./tmp/get_next_line_utils.c \
		./tmp/get_next_line.c \
		./srcs/parsing.c \
		./srcs/minishell.c \
		./main.c

OBJS_DIR =		objs

OBJS =	$(SRCS:%.c=$(OBJS_DIR)/%.obj)

DEPS =	$(OBJS:%.obj=%.d)

INCLUDES =	-I ./includes/ -I $(LIBFT_P)/ -I .

CFLAGS =	-Wall -Wextra -MMD #-Werror

LIBFT_P		=	#./libft

LIB	=	#$(LIBFT_P)/libft.a \

# ############## #
#*    REGLES    *#
# ############## #

all: _colorY_ $(NAME) _colorG_

#	make -C $(LIBFT_P)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) $(MLX) -o $@

$(OBJS_DIR)/%.obj: %.c
	@mkdir -p $(@D)
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

_colorY_:
	@echo "$(YELLO)Compilation en cours... ⚙️\n"

_colorR_:
	@echo "$(RED_B)"

_colorG_:
	@echo "$(GREEN_B)Compilation terminée 🗿\n$(CLASSIC)"

clean: _colorR_
	rm $(LIBFT_P)/$(OBJS_DIR) -rf
	rm $(OBJS_DIR) -rf

fclean: clean
	rm $(LIB) -f
	rm $(NAME) -f
	@echo "Tout à été supprimé... 🗑️\n$(CLASSIC)"

#libft: _colorY_
#	make -C $(LIBFT_P)

re: fclean all

.PHONY: all clean fclean libft re
-include $(DEPS)
