/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   owsequence.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:10:09 by bama              #+#    #+#             */
/*   Updated: 2024/06/20 13:08:07 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	owsequence_si(const char *text, const char *mask, int *i, int size)
{
	int	masksize;
	int	occurence;
	int	j;

	masksize = ft_strlen(mask);
	occurence = 0;
	while (*i < size)
	{
		j = 0;
		while (mask[j])
		{
			if (text[*i + j] != mask[j])
				return (occurence);
			j++;
		}
		occurence++;
		*i += masksize;
	}
	return (occurence);
}

int	owsequence_s(const char *text, const char *mask, int size)
{
	int	masksize;
	int	occurence;
	int	i;
	int	j;

	masksize = ft_strlen(mask);
	occurence = 0;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (mask[j])
		{
			if (text[i + j] != mask[j])
				return (occurence);
			j++;
		}
		occurence++;
		i += masksize;
	}
	return (occurence);
}

int	owsequence_i(const char *text, const char *mask, int *i)
{
	int	masksize;
	int	occurence;
	int	j;

	masksize = ft_strlen(mask);
	occurence = 0;
	while (text[*i])
	{
		j = 0;
		while (mask[j])
		{
			if (text[*i + j] != mask[j])
				return (occurence);
			j++;
		}
		occurence++;
		*i += masksize;
	}
	return (occurence);
}

int	owsequence(const char *text, const char *mask)
{
	int	masksize;
	int	occurence;
	int	i;
	int	j;

	masksize = ft_strlen(mask);
	occurence = 0;
	i = 0;
	while (text[i])
	{
		j = 0;
		while (mask[j])
		{
			if (text[i + j] != mask[j])
				return (occurence);
			j++;
		}
		occurence++;
		i += masksize;
	}
	return (occurence);
}
