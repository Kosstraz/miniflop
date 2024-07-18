/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_printf.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:09:36 by ymanchon          #+#    #+#             */
/*   Updated: 2024/06/17 11:13:54 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_PRINTF_H
# define LIBFT_PRINTF_H

# define LFORMAT "cspiudxX%"
# define __FLAG_ "# +"

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "../../libft.h"

/* /////////////////////////
////		BONUS		////
////////////////////////  */

/*
	'#' -> Avec 'x' ajoute le prefixe '0x'
	'#' -> Avec 'X' ajoute le prefixe '0X'
	' ' -> Ajoute un espace pour les 'd' et 'i'
	'+' -> Ajoute un '+' si le nombre ('d' ou 'i') est >= 0
*/

/*
	'#' -> Avec 'x' ajoute le prefixe '0x'
	'#' -> Avec 'X' ajoute le prefixe '0X'
	'*'-> '*' etant un entier : printf("%96d", 42) il y aura 96 espaces
	'*'-> Fonctionne avec tout, et il faut que l'entier 
			indique soit colle au lformat
	' ' -> Ajoute un espace pour les 'd' et 'i' si ' *' n'est pas trouve
	'+' -> Ajoute un '+' si le nombre ('d' ou 'i') est >= 0
*/

typedef struct s_flags_info
{
	int	diez;
	int	space;
	int	width;
	int	plus;
}	t_flags_info;

char	is_lformat(char c);
char	is_flag(char c);
int		ft_atoi_printf(const char *str);
void	skip_digits(const char *msg, int *i);
char	is_digit(char c);
void	add_flag(t_flags_info *finfo, char flag);
void	init_flag(t_flags_info *finfo);
int		ft_printf_handle_flags(char c, t_flags_info finfo, va_list *args);
int		ft_printf_parse_bonus(const char *msg, int *i, va_list *args);

/* /////////////////////////////
////		MANDATORY		////
///////////////////////////// */

//int		ft_strlen(const char *str);
int		ft_putstr(const char *str);
int		ft_puthexa(char *hexa);
int		ft_putchar(char c);
int		ft_putnbr(int n, int len);
int		ft_putunbr(unsigned int n, int len);
void	ft_swapchr(char **str, unsigned long size);
char	*ft_toupper_str(char *s);
int		ft_intlen(int n);
int		ft_uintlen(unsigned int n);
char	*charrefact(char *ez, int at);
char	*ft_ith(int n, char c);
char	*ft_adth(const void *ptr, const char *base);

#endif
