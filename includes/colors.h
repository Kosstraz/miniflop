/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:52:14 by bama              #+#    #+#             */
/*   Updated: 2024/08/06 23:58:51 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# define RESET		"\e[m"

/* ******************************************** */
/*		 __    _     __  _____  ___   _			*/
/*		/ /`  | | | ( (`  | |  / / \ | |\/|		*/
/*		\_\_, \_\_/ _)_)  |_|  \_\_/ |_|  |		*/
/*												*/
/* ******************************************** */

# define TPROMPT_COLOR	"\e[38;2;0;235;200m"

# define LINE_SEXY		"\e[58:2:211:54:130m"
# define LINE_ORANGE	"\e[58:2:100:255:0m"
# define LINE_RED		"\e[58:2:255:0:0m"
# define LINE_YELLOW	"\e[58:2:255:255:0m"
# define LINE_GREEN		"\e[58:2:0:255:0m"
# define LINE_BLUE		"\e[58:2:0:0:255m"
# define LINE_CYAN		"\e[58:2:0:255:255m"
# define LINE_MAGENTA	"\e[58:2:255:0:255m"

# define BACKG_SEXY		"\e[48;2;211;54;130m"
# define BACKG_RED		"\e[48;2;255;0;0m"
# define BACKG_YELLOW	"\e[48;2;255;255;0m"
# define BACKG_GREEN	"\e[48;2;0;255;0m"
# define BACKG_BLUE		"\e[48;2;0;0;255m"
# define BACKG_CYAN		"\e[48;2;0;255;255m"
# define BACKG_MAGENTA	"\e[48;2;255;0;255m"

# define TEXT_SEXY		"\e[38;2;211;54;130m"
# define TEXT_RED		"\e[38;2;255;0;0m"
# define TEXT_YELLOW	"\e[38;2;255;255;0m"
# define TEXT_GREEN		"\e[38;2;0;255;0m"
# define TEXT_BLUE		"\e[38;2;0;0;255m"
# define TEXT_CYAN		"\e[38;2;0;255;255m"
# define TEXT_MAGENTA	"\e[38;2;255;0;255m"

/* **************************************************** */
/*		 ____  ____  ____  ____  __   _____  __			*/
/*		| |_  | |_  | |_  | |_  / /`   | |  ( (`		*/
/*		|_|__ |_|   |_|   |_|__ \_\_,  |_|  _)_)		*/
/*														*/
/* **************************************************** */

# define CURLY			"\e[4:3m"
# define R_CURLY		"\e[4:0m"

# define BOLD			"\e[1m"
# define OPACITY		"\e[2m"
# define ITALIC 		"\e[3m"
# define UNDERLINE		"\e[4m"
# define BLINK			"\e[5m"
# define REV_COLOR		"\e[7m"
# define HIDDEN			"\e[8m"
# define CENTRALLINE	"\e[9m"

# define DUNDERLINE		"\e[21m"
# define R_DUNDERLINE	"\e[24m"

# define R_HIDDEN		"\e[28m"
# define R_CENTRALLINE	"\e[29m"

# define OVERLINE		"\e[53m"
# define R_OVERLINE		"\e[55m"

/* **************************************************** */
/*		 ___   ____  ____   __    _     _    _____		*/
/*		| | \ | |_  | |_   / /\  | | | | |    | |		*/
/*		|_|_/ |_|__ |_|   /_/--\ \_\_/ |_|__  |_|		*/
/*														*/
/* **************************************************** */

# define RED		"\e[31m"
# define GREEN		"\e[32m"
# define BLUE		"\e[34m"
# define YELLOW		"\e[93m"

#endif