# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bama <bama@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 16:21:19 by ymanchon          #+#    #+#              #
#    Updated: 2024/08/10 14:07:47 by bama             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ################ #
#*    COULEURS    *#
# ################ #

CLASSIC	= \e[0m
WHITE	= \e[38;2;238;232;213m
BOLD	= \e[1m
# BLACK	= \e[38;2;0;0;0m
BLACK	= \e[30m
RED   	= \e[31m
GREEN  	= \e[32m
BLUE 	= \e[38;2;0;36;148m
PURPLE 	= \e[38;2;211;54;130m
CYAN   	= \e[36m
YELLOW 	= \e[38;2;250;189;0m

# ############### #
#*   VARIABLES   *#
# ############### #

NAME = minishell

CC = @cc

SRCS =	./srcs/termcap/tab/select.c \
		./srcs/termcap/tab/switch.c \
		./srcs/termcap/tab/utils.c \
		./srcs/termcap/tab/tab.c \
		./srcs/termcap/arrow_keys.c \
		./srcs/termcap/copy_paste.c \
		./srcs/termcap/delete_keys.c \
		./srcs/termcap/free_terminal.c \
		./srcs/termcap/ft_readline.c \
		./srcs/termcap/printables.c \
		./srcs/termcap/term_initialise.c \
		./srcs/termcap/utils.c \
		\
		./srcs/parsing/check_parse_error.c \
		./srcs/parsing/utils.c \
    	./srcs/parsing/ft_split_quotes2.c \
		./srcs/parsing/ft_split_quotes.c \
		./srcs/parsing/token_id2.c \
		./srcs/parsing/token_id.c \
		./srcs/parsing/token_utils.c \
		./srcs/parsing/jokeroverride.c \
		./srcs/parsing/jokeroverride2.c \
		./srcs/parsing/parsing_quotes.c \
		./srcs/parsing/envvar.c \
		./srcs/parsing/separate_operands.c \
		./srcs/parsing/parsing.c \
		./srcs/parsing/token_parseerror.c \
		\
		./srcs/builtins/cd.c \
		./srcs/builtins/cd2.c \
		./srcs/builtins/echo.c \
		./srcs/builtins/exit.c \
		./srcs/builtins/env.c \
		./srcs/builtins/export_args.c \
		./srcs/builtins/export.c \
		./srcs/builtins/pwd.c \
		./srcs/builtins/unset.c \
		./srcs/builtins/hdel.c \
		\
		./srcs/exec/search_cmd.c \
		./srcs/exec/exec.c \
		./srcs/exec/blt_utils.c \
		./srcs/exec/cwd_utils.c \
		./srcs/exec/tok_utils.c \
		./srcs/exec/tok_utils2.c \
		./srcs/exec/pipe_utils.c \
		./srcs/exec/redirections_utils.c \
		./srcs/exec/utils.c \
		./srcs/exec/utils2.c \
		\
		./srcs/history/history.c \
		./srcs/history/history2.c \
		\
		./srcs/debug.c \
		./srcs/prompts.c \
		./srcs/prompts2.c \
		./srcs/data_handling.c \
		./srcs/env_utils.c \
		./srcs/env_utils2.c \
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

TLIB = -ltermcap \

# ############## #
#*    REGLES    *#
# ############## #

all: libft_comp pre_comp  $(NAME) #mischief

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) $(TLIB) -o $@
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
	@echo "\t\t╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗"
	@sleep 0.008
	@echo "\t\t╠╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╣"
	@sleep 0.008
	@echo "\t\t╠╣                                               ╠╣"
	@sleep 0.008
	@echo "\t\t╠╣                                               ╠╣"
	@sleep 0.008
	@echo "\t\t╠╣     __    __     __     __   __     __        ╠╣"
	@sleep 0.008
	@echo "\t\t╠╣    /\ '-./  \   /\ \   /\ '-.\ \   /\ \       ╠╣"
	@sleep 0.008
	@echo "\t\t╠╣    \ \ \-./\ \  \ \ \  \ \ \-.  \  \ \ \      ╠╣"
	@sleep 0.008
	@echo "\t\t╠╣     \ \_\ \ \_\  \ \_\  \ \_\/'\_\  \ \_\     ╠╣"
	@sleep 0.008
	@echo "\t\t╠╣      \/_/  \/_/   \/_/   \/_/ \/_/   \/_/     ╠╣"
	@sleep 0.008
	@echo "\t\t╠╣                                               ╠╣"
	@sleep 0.008
	@echo "\t\t╠╣     ______   __         ______     ______     ╠╣"
	@sleep 0.008
	@echo "\t\t╠╣    /\  ___\ /\ \       /\  __ \   /\  == \    ╠╣"
	@sleep 0.008
	@echo "\t\t╠╣    \ \  __\ \ \ \____  \ \ \/\ \  \ \  _-/    ╠╣"
	@sleep 0.008
	@echo "\t\t╠╣     \ \_\    \ \_____\  \ \_____\  \ \_\      ╠╣"
	@sleep 0.008
	@echo "\t\t╠╣      \/_/     \/_____/   \/_____/   \/_/      ╠╣"
	@sleep 0.008
	@echo "\t\t╠╣                                               ╠╣"
	@sleep 0.008
	@echo "\t\t╠╣                                               ╠╣"
	@sleep 0.008
	@echo "\t\t╠╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╣"
	@sleep 0.008
	@echo "\t\t╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝"
	@sleep 0.008
	@echo "$(CLASSIC)"
	@echo "$(YELLOW)"

mischief:
	@echo "$(WHITE)$(BLACK)@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@sleep 0.01
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@$(YELLOW)%(/(############(/(%$(BLACK)@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@sleep 0.01
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@$(YELLOW)((############################(($(BLACK)@@@@@@@@@@@@@@@@@@@@"
	@sleep 0.01
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@$(YELLOW)/########%%%%%%%%%%%%%%%%%%%%##########/$(BLACK)@@@@@@@@@@@@@@@@"
	@sleep 0.01
	@echo "@@@@@@@@@@@@@@@@@@@@@$(YELLOW)/######%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#######/&$(BLACK)@@@@@@@@@@@@"
	@sleep 0.01
	@echo "@@@@@@@@@@@@@@@@@@$(YELLOW)######%#%&@@@@@@@@@@&%%%%%%%%%%%%%%%%%%%%%%%%######($(BLACK)@@@@@@@@@@"
	@sleep 0.01
	@echo "@@@@@@@@@@@@@@@@$(YELLOW)(####%@@@@@@@@@@@&&&&&&&&&&&&%%%%%%%%%%%%%%%%%%%%######/$(BLACK)@@@@@@@@"
	@sleep 0.01
	@echo "@@@@@@@@@@@@@@$(YELLOW)%####@@@@@@@@@@@&&&&&&&&&&&&&&&&&&%%%%%%%%%%%%%%%%%%%#######$(BLACK)@@@@@@"
	@sleep 0.01
	@echo "@@@@@@@@@@@@@$(YELLOW)/##%@@@@@@@@@@&&&&&&&&&&&&&&&&&&&&&&&&%%%%%%%%%%%%%%%%%%###%%/$(BLACK)@@@@@"
	@sleep 0.01
	@echo "@@@@@@@@@@@@$(YELLOW)(##&@@@@@@@&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&%%%%%%%%%%%%%%%%%##%%%($(BLACK)@@@@"
	@sleep 0.01
	@echo "@@@@@@@@@@@$(YELLOW)(%%&@@@@@&&&&&&&&&&&&&&&&&&&&&.*,*,,&&&&&&&%%%%%%%%%%%%%%%%%%%%%%($(BLACK)@@@"
	@sleep 0.01
	@echo "@@@@@@@@@@$(YELLOW)(##&@@&&&&&&&&&&&&&&&&&&&&&&&&.,.(%%#.&&&%#####%%%%%%%%%%%%%%%%%%&#/$(BLACK)@@"
	@sleep 0.01
	@echo "@@@@@@@@@$(YELLOW)&##%&&&&&&&&&&&&&&&&&&&&&&&&&&.,....,%%&%%####&&&&&%%%%%%%%%%%%%%%&&#$(BLACK)@@"
	@sleep 0.01
	@echo "@@@@@@@@@$(YELLOW)###&&&&&&&&&&&&&&&&&&&&&&&&&%,,,$(WHITE)#&@&&&&$(YELLOW).###%&&&%(/(((%%%%%%%%%%%%%&&#/$(BLACK)@"
	@sleep 0.01
	@echo "@@@@@@@@@$(YELLOW)(#%&&&&&&&&&&&&&&&&&&&&&&&&(,,*.*** $(WHITE)@@@$(YELLOW)&#(%%%%(/%%%%%%%%%%%%%%%%%%&&#/$(BLACK)@"
	@sleep 0.01
	@echo "@@@@@@@@@$(YELLOW)(#%&&&&&&&&&&&&&&&&&&/#&&&,,,,,$(BLUE)@*  *$(WHITE),@@@$(YELLOW)&*#%%/%%/%%%%%%%%%%%%%%%%%&&#/$(BLACK)@"
	@sleep 0.01
	@echo "@@@@@@@@@$(YELLOW)###,..*%&&&&&&&&&(.&&&.(&.,,,* $(BLUE)(   #$(WHITE).@@@$(YELLOW)&((%%%%%(%%%%%%%%%%%%%%%%%&&#($(BLACK)@"
	@sleep 0.01
	@echo "@@@@@@@@@@$(YELLOW)(#,..,,,,,, #&&&&,.&&&.,,,,($(WHITE)%@@$(YELLOW), ,$(WHITE)@@@@@$(YELLOW)&,#%%%%%/&#%%%%%%%%%%%%%%%&%($(BLACK)@@"
	@sleep 0.01
	@echo "@@@@@@@@@@$(YELLOW)##.&&&#,$(WHITE)%%/$(YELLOW)..,,,,.,.&%%.,,%.$(WHITE)@@@@@@@@@@$(YELLOW)&,##%%%%#%&#%%%%%%%%%%%%%%%&#($(BLACK)@@"
	@sleep 0.01
	@echo "@@@@@@@@@@@$(YELLOW)/#&&%(#&$(WHITE)@@ $(BLUE)/  %$(YELLOW)*/*#%%%%%%%%#.$(WHITE)&&&&&&&$(YELLOW)*(#%%%%%##$(WHITE)&&$(YELLOW)@#%%%%%%%%%%%%%%%/$(BLACK)@@@"
	@sleep 0.01
	@echo "@@@@@@@@@@@@$(YELLOW)/%%###,$(WHITE)@@@@@@@@&$(YELLOW)/%%%%%%%%%%%########%%%%%%(&$(WHITE)@@@@$(YELLOW)#%%%%%%%%%%%%%%/$(BLACK)@@@@"
	@sleep 0.01
	@echo "@@@@@@@@@@@@@$(YELLOW)##%%%##**$(WHITE)%&&$(YELLOW)(,#%%%%%%%%%%%%%%%%%%%######/$(WHITE)@#@@@$(YELLOW)(&%%%%%%%%%##%#($(BLACK)@@@@@"
	@sleep 0.01
	@echo "@@@@@@@@@@@@@@@$(YELLOW)/#%%%%%%%%%%%%%%%%%%%%%%%%%%########/$(WHITE)@@@@(@@$(YELLOW)%%%%%%%%%%###/$(BLACK)@@@@@@@"
	@sleep 0.01
	@echo "@@@@@@@@@@@@@@@@@$(YELLOW)/#%%%%%%%%(#&&%#(%%#############/$(WHITE)@@@@@@@($(YELLOW)%%%%%%%%%###(&$(BLACK)@@@@@@@@"
	@sleep 0.01
	@echo "@@@@@@@@@@@@@@@@@@@$(YELLOW)/##%%%%#%&&%%%#(#%#######%#/$(WHITE)(@@@@@@@&($(YELLOW)&%%%%%%%###/$(BLACK)@@@@@@@@@@@"
	@sleep 0.01
	@echo "@@@@@@@@@@@@@@@@$(YELLOW)((#(/#/##(/%%%%%%####((###(#$(WHITE)@@@@#@@@@/$(YELLOW)&&%##%%%###/&$(BLACK)@@@@@@@@@@@@@"
	@sleep 0.01
	@echo "@@@@@@@@@@@@@@@@@$(YELLOW)%%%%###%%%%%%(%%%%%%%@@@@%$(WHITE)((%&&%###$(YELLOW)%#%##/#\/#\\#$(BLACK)@@@@@@@@@@@@@@@@"
	@sleep 0.01
	@echo "@@@@@@@@@@@@@@@$(YELLOW)(%&&%%%%%%%%%%##%%%%%%%%%&&&/%#%#(#%#%####/%$(BLACK)@@@@@@@@@@@@@@@@@@@@@"
	@sleep 0.01
	@echo "@@@@@@@@@@@@@@@@@@@@@@$(YELLOW)(%%%%(%&&&&&%%%%%%%&&%////(##&$(BLACK)@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@sleep 0.01
	@echo "@@@@@@@@@@@@@@@@@@@@$(YELLOW)(%%%/&&&&&&&&&&&%%%%%%&%#$(BLACK)@@@@@#$(BLACK)@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@sleep 0.01
	@echo "@@@@@@@@@@@@@@@@@$(YELLOW)%(%%##&&&%&&&&&&&&&%%%%%%%($(BLACK)@@@@@@#$(BLACK)@@@&@@@@@@@@@@@@@@@@@@@@@@@@@"
	@sleep 0.01
	@echo "@@@@@@@@@@@@@@$(YELLOW)/%%%%##&&&&%&&&&&%&&&&%%%%%%/$(BLACK)@@@@@@#$(BLACK)@@@@($(BLACK)@@@@@@@@@@@@@@@@@@@@@@@@@"
	@sleep 0.01
	@echo "@@@@@@@@@@@$(YELLOW)(&&&%%%/&&&&%%%&##&&&&&%%#(%#($(BLACK)@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@sleep 0.01
	@echo "@@@@@@%@@@$(YELLOW)/&&%%%%/&&&%%%%/&&&%%%(#%%/&$(BLACK)@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@sleep 0.01
	@echo "@@(@@@(@@@@$(YELLOW)/%%%%#/%%%%#(&&%%%%/%#($(BLACK)@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@sleep 0.01
	@echo "@@/@@@@(@@@$(YELLOW)/##%%%%%(%&&%%%%###($(BLACK)@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@sleep 0.01
	@echo "@@@@@@@@@#@$(YELLOW)%/%&&&#/%/%%#%/(&$(BLACK)@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@sleep 0.01
	@echo "@@@@@@@@@@@@@@@$(YELLOW)&/##(($(BLACK)@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n$(CLASSIC)"
