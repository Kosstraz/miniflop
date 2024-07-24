# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cachetra <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 16:21:19 by ymanchon          #+#    #+#              #
#    Updated: 2024/07/23 18:29:22 by cachetra         ###   ########.fr        #
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

SRCS =	./srcs/parsing/utils.c \
		./srcs/parsing/ft_split_quotes2.c \
		./srcs/parsing/ft_split_quotes.c \
		./srcs/parsing/token_id2.c \
		./srcs/parsing/token_id.c \
		./srcs/parsing/parsing_wildcards2.c \
		./srcs/parsing/parsing_wildcards.c \
		./srcs/parsing/parsing_quotes.c \
		./srcs/parsing/envvar.c \
		./srcs/parsing/separate_operands.c \
		./srcs/parsing/parsing.c \
		./srcs/builtins/exit.c \
		./srcs/builtins/echo.c \
		./srcs/builtins/cd.c \
		./srcs/debug.c \
		./srcs/data_handling.c \
		./srcs/signals_handling.c \
		./srcs/minishell.c \
		./main.c \
		./term/ez.c \

OBJS_DIR =		objs

OBJS =	$(SRCS:%.c=$(OBJS_DIR)/%.obj)

DEPS =	$(OBJS:%.obj=%.d)

INCLUDES =	-I ./includes/ -I $(LIBFT_P)/ -I .

CFLAGS =	-Wall -Wextra -MMD -g3 -ltermcap #-Werror

LIBFT_P		=	./libft

LIB	=	$(LIBFT_P)/libft.a \

# ############## #
#*    REGLES    *#
# ############## #

all: _colorY_ $(NAME) _colorG_

$(NAME): $(OBJS)
	make -C $(LIBFT_P)
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

libft: _colorY_
	make -C $(LIBFT_P)

re: fclean all

.PHONY: all clean fclean libft re
-include $(DEPS)
