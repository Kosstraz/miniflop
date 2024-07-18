/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:10:32 by ymanchon          #+#    #+#             */
/*   Updated: 2024/05/29 14:03:50 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_split_free(char **tofree, size_t count)
{
	while (count > 0)
	{
		if (tofree[count])
			free(tofree[count--]);
	}
	if (tofree[0])
		free(tofree[0]);
	free(tofree);
}

static char	*strdup_at(const char *str, ssize_t start, ssize_t end)
{
	size_t	i;
	size_t	size;
	char	*ret;

	size = end - start;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (NULL);
	ret[size] = '\0';
	i = 0;
	while (start < end)
		ret[i++] = str[start++];
	return (ret);
}

static ssize_t	skip_sep(const char *s, size_t *i, size_t *old, char sep)
{
	while (s[*i] == sep)
		(*i)++;
	if (!s[*i])
		return (-1);
	*old = *i;
	while (s[*i] != sep && s[*i])
		(*i)++;
	return (*i);
}

char	**ft_split(const char *s, char sep)
{
	char	**ret;
	size_t	back;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	ret = (char **)malloc(sizeof(char *) * (ft_count_words(s, sep) + 1));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (skip_sep(s, &i, &back, sep) == -1)
			break ;
		ret[j] = strdup_at(s, back, i);
		if (!ret[j++])
		{
			ft_split_free(ret, j - 1);
			return (NULL);
		}
	}
	ret[j] = NULL;
	return (ret);
}

/*int main(void)
{
	printf("%s\n", ft_split("^^^1^^2a,^^^^3^^^^--h^^^^", '^'));	
	return (0);
}*/
