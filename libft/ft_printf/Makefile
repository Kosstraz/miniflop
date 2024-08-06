# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 16:21:19 by ymanchon          #+#    #+#              #
#    Updated: 2024/08/06 17:45:26 by cachetra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ################ #
#*    COULEURS    *#
# ################ #

CLASSIC = \e[0m
BOLD	= \e[1m
RED   	= \e[31m
GREEN 	= \e[32m
YELLOW  = \e[93m
CYAN	= \e[36m

# ############### #
#*   VARIABLES   *#
# ############### #

NAME = libftprintf.a

CC =	@cc

AR =  ar -rcs

SRCS =	./srcs/ft_printf_utils.c \
		./srcs/ft_printf_utils2.c \
		./srcs/ft_hexa.c \
		./srcs/ft_showptr.c \
		./srcs/ft_printf.c \
		./bonus/ft_printf_utils_bonus.c \
		./bonus/ft_printf_utils2_bonus.c \
		./bonus/ft_printf_handle_bonus.c \

OBJS_DIR =		objs

OBJS =	$(SRCS:%.c=$(OBJS_DIR)/%.o)

OBJS_BONUS =	$(SRCS_BONUS:%.c=$(OBJS_DIR)/%.o)

INCLUDES = -I . -I ./includes/

CFLAGS =	-Wall -Wextra -Werror -fPIE

# ############## #
#*    REGLES    *#
# ############## #

all: $(OBJS)

#$(NAME): $(OBJS)
#	$(AR) -o $@ $(OBJS)

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo "$(GREEN)🗸 Compilation $(BOLD)$(YELLOW)$<$(CLASSIC)"
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(BOLD)$(RED)"
	@rm $(OBJS_DIR) -rf
	@echo "$(CLASSIC)"

fclean: clean
	 @rm $(NAME) -f

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
