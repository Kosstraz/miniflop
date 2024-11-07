/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:59:44 by bama              #+#    #+#             */
/*   Updated: 2024/11/07 15:25:48 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt_add_retcmd(char *prompt, t_data *data);
char	*replace_home_by_tild(char *cwd, t_data *data);
t_rgb	create_rgb(int r, int g, int b);

static char	*create_color_ascii(int r, int g, int b)
{
	char	*color;
	char	*itoa;

	itoa = ft_itoa(r);
	color = ft_strjoin("\e[38;2;", itoa);
	free(itoa);
	color = strljoin(color, ";");
	itoa = ft_itoa(g);
	color = strljoin(color, itoa);
	free(itoa);
	color = strljoin(color, ";");
	itoa = ft_itoa(b);
	color = strljoin(color, itoa);
	free(itoa);
	color = strljoin(color, "m");
	return (color);
}

static void	increment_color(int lvl[3], t_rgb *rgb, t_rgb inc)
{
	if (rgb->r <= 0)
		lvl[0] = 1;
	else if (rgb->r >= 255)
		lvl[0] = -1;
	if (rgb->g <= 0)
		lvl[1] = 1;
	else if (rgb->g >= 255)
		lvl[1] = -1;
	if (rgb->b <= 0)
		lvl[2] = 1;
	else if (rgb->b >= 255)
		lvl[2] = -1;
	rgb->r += inc.r * lvl[0];
	rgb->g += inc.g * lvl[1];
	rgb->b += inc.b * lvl[2];
}

// 0 235 185
// s --> start value RGB
// i --> increment RGB values, respectivly
char	*create_shading(char *normal_prompt, t_rgb s, t_rgb inc)
{
	t_rgb	rgb;
	int		i;
	int		lvl[3];
	char	c[2];
	char	*new;

	i = 0;
	ft_memset((int *)lvl, (-1), 3 * sizeof(int));
	rgb.r = s.r + ((ft_strlen(normal_prompt)) / 2);
	rgb.g = s.g + ((ft_strlen(normal_prompt)) / 2);
	rgb.b = s.b + ((ft_strlen(normal_prompt)) / 2);
	new = ft_strdup(BOLD);
	while (normal_prompt[i])
	{
		increment_color(lvl, &rgb, inc);
		c[0] = normal_prompt[i];
		c[1] = 0;
		new = strlljoin(new, create_color_ascii(rgb.r, rgb.g, rgb.b));
		new = strljoin(new, c);
		i++;
	}
	new = strljoin(new, RESET);
	free(normal_prompt);
	return (new);
}

void	add_at_to_env(char *value, t_data *data)
{
	if (!env_exist(CWD_AT_NAME, data))
		add_new_env(ft_strdup(CWD_AT_NAME), value, &data->env);
	else
		setenvval(CWD_AT_NAME, value, &data->env);
}

void	new_prompt(char **buffer_prompt, t_data *data)
{
	char	*cwd;
	char	*tmp;
	int		size;

	cwd = getcwd(NULL, 0);
	cwd = replace_home_by_tild(cwd, data);
	size = ft_strlen(cwd);
	if (size > CWD_MAX_LEN)
	{
		while (cwd[size - CWD_MAX_LEN] && cwd[size - CWD_MAX_LEN] != '/')
			size++;
		add_at_to_env(ft_strdup_at(cwd, 0, size - CWD_MAX_LEN), data);
		cwd = ft_strldup_at(cwd, size - CWD_MAX_LEN, size);
		tmp = cwd;
		cwd = ft_strjoin("@", cwd);
		free(tmp);
	}
	else
		if (env_exist(CWD_AT_NAME, data))
			env_remove(CWD_AT_NAME, &data->env);
	*buffer_prompt = prompt_add_retcmd(*buffer_prompt, data);
	*buffer_prompt = strlljoin(*buffer_prompt, cwd);
	*buffer_prompt = strljoin(*buffer_prompt, PROMPT2);
	*buffer_prompt = create_shading(*buffer_prompt, create_rgb(0, 235, 185), create_rgb(3, 2, -3));
	data->prompt = (*buffer_prompt);
}
