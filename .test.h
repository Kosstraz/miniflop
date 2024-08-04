/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .test.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:56:45 by bama              #+#    #+#             */
/*   Updated: 2024/08/04 14:23:39 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <unistd.h>

struct s_openf	openf(const char *filepath, int oflags, int mode);
void			closef(struct s_openf *openfile);
void			reopenf(struct s_openf *openfile);

typedef struct s_openf
{
	const char	*file_path;
	int			oflags;
	int			mode;
	int			fd;
}	t_openf;