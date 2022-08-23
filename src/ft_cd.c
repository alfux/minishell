/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:40:11 by alfux             #+#    #+#             */
/*   Updated: 2022/08/23 14:59:12 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_replace(char **pwd, char **old)
{
	size_t	size;
	char	*new;
	char	*buf;

	buf = ft_newpwd();
	if (!buf)
		return (1);
	size = ft_strlen(buf);
	new = ft_calloc(size + 5, sizeof (char));
	if (!new)
		return (1 + ft_free(buf));
	free(*old);
	*old = *pwd;
	**old = 'O';
	*(*old + 1) = 'L';
	*pwd = new;
	ft_strlcpy(*pwd, "PWD=", size + 5);
	ft_strlcpy(*pwd + 4, buf, size + 1);
	return (ft_free(buf));
}

int	ft_cd(char **av, char **ev)
{
	int		i;

	if (chdir(*(av + 1)))
		return (ft_errmsg(errno));
	i = 0;
	while (*(ev + i))
	{
		if (!ft_strncmp(*(ev + i), "PWD=", 4))
			if (ft_replace(ev + i, ev + i + 1))
				return (ft_errmsg(errno));
		i++;
	}
	return (0);
}
