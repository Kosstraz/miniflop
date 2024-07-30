# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bama <bama@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 16:21:19 by ymanchon          #+#    #+#              #
#    Updated: 2024/07/30 14:56:10 by bama             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ################ #
#*    COULEURS    *#
# ################ #

CLASSIC= \e[0m
BOLD	= \e[1m
RED   	= \e[31m
GREEN  = \e[32m
YELLOW = \e[33m
PURPLE = \e[35m
CYAN   = \e[36m

# ############### #
#*   VARIABLES   *#
# ############### #

NAME = minishell

CC = @cc

SRCS = ./srcs/parsing/utils.c \
       ./srcs/parsing/utils2.c \
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
	   \
       ./srcs/builtins/exit.c \
	   ./srcs/builtins/unset.c \
       ./srcs/builtins/echo.c \
       ./srcs/builtins/cd.c \
	   \
	   ./srcs/exec/search_cmd.c \
	   ./srcs/exec/exec.c \
	   ./srcs/exec/utils.c \
	   \
       ./srcs/debug.c \
       ./srcs/prompts.c \
       ./srcs/data_handling.c \
	   ./srcs/data_handling2.c \
       ./srcs/signals_handling.c \
       ./srcs/minishell.c \
	   \
       ./main.c

LMAKE = @make --no-print-directory -C

OBJS_DIR = objs

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.obj)

DEPS = $(OBJS:%.obj=%.d)

INCLUDES = -I ./includes/ -I $(LIBFT_P)/ -I .

CFLAGS = -Wall -Wextra -MMD -g3 #-Werror

LIBFT_P = ./libft

LIB = $(LIBFT_P)/libft.a \

# ############## #
#*    REGLES    *#
# ############## #

all: libft_comp pre_comp $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $@
	@echo "$(BOLD)$(CYAN)Exécutable $(NAME) créé avec succès!$(CLASSIC)"

$(OBJS_DIR)/%.obj: %.c
	@mkdir -p $(@D)
	@echo "$(GREEN)🗸 Compilation $(BOLD)$(YELLOW)$<$(CLASSIC)"
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(BOLD)$(RED)"
	rm $(LIBFT_P)/$(OBJS_DIR) -rf
	rm $(OBJS_DIR) -rf
	@echo "$(CLASSIC)"

fclean: clean
	@echo "$(BOLD)$(RED)"
	rm $(LIB) -f
	rm $(NAME) -f
	@echo "$(BOLD)$(GREEN)Tout a été supprimé... 🗑️\n$(CLASSIC)"

re: fclean all

.PHONY: all clean fclean re
-include $(DEPS)

# ############## #
#*    AUTRES    *#
# ############## #

# Permet de compiler la libft avant $(NAME)
libft_comp:
	$(LMAKE) $(LIBFT_P)

pre_comp:
	@echo "$(BOLD)"
	@echo "$(PURPLE)"
	@echo "***********************************************"
	@echo "***************** MINISHELL *******************"
	@echo "***********************************************"
	@echo "$(CLASSIC)"