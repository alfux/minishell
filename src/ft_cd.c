/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:40:11 by alfux             #+#    #+#             */
/*   Updated: 2022/08/16 14:33:26 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_replace(char **pwd, char **old)
{
	size_t	size;
	char	*new;
	char	*buf;

	size = ft_strlen(*pwd);
	new = ft_calloc(size + 4, sizeof (char));
	if (!new)
		return (ft_errmsg(errno));
	free(*old);
	*old = new;
	ft_strlcpy(new, "OLD", size + 4);
	ft_strlcat(new, *pwd, size + 4);
	buf = ft_newpwd();
	if (!buf)
		return (errno);
	size = ft_strlen(buf);
	new = ft_calloc(size + 5, sizeof (char));
	if (!new)
		return (ft_errmsg(errno) + ft_free(buf));
	free(*pwd);
	*pwd = new;
	ft_strlcpy(*pwd, "PWD=", size + 5);
	ft_strlcat(*pwd, buf, size + 5);
	return (ft_free(buf));
}

int	ft_cd(char **path, char **ev)
{
	int		i;

	if (chdir(*(path + 1)))
		return (ft_errmsg(errno));
	i = 0;
	while (*(ev + i))
	{
		if (!ft_strncmp(*(ev + i), "PWD=", 4))
			if (ft_replace(ev + i, ev + i + 1))
				return (errno);
		i++;
	}
	return (0);
}
