/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .test.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 02:56:15 by bama              #+#    #+#             */
/*   Updated: 2024/08/09 01:39:24 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".test.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int	ft_intlen_itoa(int n)
{
	int	n_len;

	n_len = 0;
	while (n > 0)
	{
		n_len++;
		n /= 10;
	}
	return (n_len);
}

static char	*ft_itoa_int_min(void)
{
	char	*ret;
	int		n;
	int		n_len;

	ret = (char *)malloc(12);
	if (!ret)
		return ((char *)0);
	ret[0] = '-';
	ret[11] = '\0';
	ret[10] = '8';
	n = 214748364;
	n_len = 9;
	while (n_len >= 1)
	{
		ret[n_len--] = n % 10 + '0';
		n /= 10;
	}
	return (ret);
}

static char	*ft_itoa_zero(void)
{
	char	*ret;

	ret = (char *)malloc(2);
	if (!ret)
		return ((char *)0);
	ret[0] = '0';
	ret[1] = '\0';
	return (ret);
}

static char	*ft_itoa_neg(long n)
{
	char	*ret;
	int		n_len;

	if (n == -2147483648)
		return (ft_itoa_int_min());
	n_len = ft_intlen_itoa(n);
	ret = (char *)malloc(n_len + 2);
	if (!ret)
		return ((char *)0);
	ret[0] = '-';
	ret[n_len + 1] = '\0';
	while (n_len >= 1)
	{
		ret[n_len--] = n % 10 + '0';
		n /= 10;
	}
	return (ret);
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		n_len;

	if (n == 0)
		return (ft_itoa_zero());
	if (n < 0)
		return (ft_itoa_neg(-n));
	n_len = ft_intlen_itoa(n);
	ret = (char *)malloc(n_len + 1);
	if (!ret)
		return ((char *)0);
	ret[n_len--] = '\0';
	while (n_len >= 0)
	{
		ret[n_len--] = n % 10 + '0';
		n /= 10;
	}
	return (ret);
}

char	*ft_strdup(const char *str)
{
	char			*ret;
	unsigned long	alloc_size;
	unsigned long	i;

	if (!str)
		return (NULL);
	alloc_size = strlen(str);
	ret = (char *)malloc(sizeof(char) * (alloc_size + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*ret;
	int		size1;
	int		size2;
	int		i;
	int		n;

	size1 = strlen(s1);
	size2 = strlen(s2);
	ret = (char *)malloc(size1 + size2 + 1);
	if (!ret)
		return ((char *)0);
	i = 0;
	n = 0;
	while (s1[i])
		ret[n++] = s1[i++];
	i = 0;
	while (s2[i])
		ret[n++] = s2[i++];
	ret[n] = '\0';
	return (ret);
}

static int	ft_isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}

int	ft_tolower(int c)
{
	if (ft_isupper(c))
		return (c += 32);
	return (c);
}

char	*ft_strtolower(char *str)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

int	main(void)
{
	char	*ez;
	char	*tolower;

	ez = ft_strdup("EZAFds fsdf es EEQF");
	tolower = ft_strtolower(ft_strdup(ez));
	printf("ez %s\ntolower %s\n", ez, tolower);
	/*int	r, g, b;
	int	back[3];

	back[0] = 0;
	back[1] = 0;
	back[2] = 0;
	r = 0;
	g = 0;
	b = 0;
	while (1)
	{
		char	*ez;

		ez = ft_strdup("\e[38;2;");
		ez = ft_strjoin(ez, ft_itoa(r));
		ez = ft_strjoin(ez, ";");
		ez = ft_strjoin(ez, ft_itoa(g));
		ez = ft_strjoin(ez, ";");
		ez = ft_strjoin(ez, ft_itoa(b));
		ez = ft_strjoin(ez, "m");
		printf("%s╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣╠╣\e[0m\n", ez);
		if (r >= 255)
			back[0] = 1;
		else if (r <= 0)
			back[0] = 0;
		if (g >= 255)
			back[1] = 1;
		else if (g <= 0)
			back[1] = 0;
		if (b >= 255)
			back[2] = 1;
		else if (b <= 0)
			back[2] = 0;
		if (back[0])
			r -= 3;
		else
			r += 1;
		if (back[1])
			g -= 2;
		else
			g += 2;
		if (back[2])
			b -= 1;
		else
			b += 3;
		usleep(20000);
	}
	
	for (int k = 5 ; k < 6 ; k++)
	{
		for (int i = 0 ; i < 99 ; i++)
		{
			for (int j = 0 ; j < 99 ; j++)
			{
				char	*ascii;

				ascii = ft_strdup("\e[");
				ascii = ft_strjoin(ascii, ft_itoa(k));
				ascii = ft_strjoin(ascii, ":");
				ascii = ft_strjoin(ascii, ft_itoa(i));
				ascii = ft_strjoin(ascii, ":");
				ascii = ft_strjoin(ascii, ft_itoa(j));
				ascii = ft_strjoin(ascii, "m");
				printf("%d:%d:%d : %s%s\e[0m", k, i, j, ascii, "Bonjour\n");
			}
		}
	}*/
	/*for (int i = 0 ; i < 99 ; i++)
	{
		for (int j = 0 ; j < 99 ; j++)
		{
			char	*ascii;

			ascii = ft_strdup("\e[");
			ascii = ft_strjoin(ascii, ft_itoa(i));
			ascii = ft_strjoin(ascii, ":");
			ascii = ft_strjoin(ascii, ft_itoa(j));
			ascii = ft_strjoin(ascii, "m");
			printf("%d:%d : \e[48;2;211;54;130m%s%s\e[0m", i, j, ascii, "Bonjour\n");
		}
	}
	for (int i = 0 ; i < 100 ; i++)
	{
		char	*ascii;

		ascii = ft_strdup("\e[");
		ascii = ft_strjoin(ascii, ft_itoa(i));
		ascii = ft_strjoin(ascii, "m");
		printf("%d : %s%s\e[0m", i, ascii, "Bonjour\n");
	}*/
	return (0);
}
