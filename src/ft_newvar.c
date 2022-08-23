/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:04:55 by alfux             #+#    #+#             */
/*   Updated: 2022/08/23 15:12:28 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	**ft_isinvar(char *candidate, char **var)
{
	size_t	size;
	int		j;

	if (!var)
		return ((char **)0);
	size = 0;
	while (*(candidate + size) && *(candidate + size) != '=')
		size++;
	j = 0;
	while (*(var + j))
	{
		if (!ft_strncmp(candidate, *(var + j), size + 1))
			return (var + j);
		j++;
	}
	return ((char **)0);
}

static int	ft_replace(char **var, char **cmd, char **cpy)
{
	char	**buf;
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (*(cmd + i))
	{
		str = ft_strdup(*(cmd + i));
		if (!str)
			return (1);
		buf = ft_isinvar(str, var);
		if (buf)
		{
			free(*buf);
			*buf = str;
		}
		else
			*(cpy + j++) = str;
		i++;
	}
	return (0);
}

char	**ft_newvar(char **cmd, char **var)
{
	char	**cpy;
	char	**new;

	if (!var)
		return (ft_strtdup(cmd));
	cpy = ft_calloc(ft_strtlen(cmd) + 1, sizeof (char *));
	if (!cpy)
		return (var + (0 * ft_errmsg(errno)));
	if (ft_replace(var, cmd, cpy))
		return (var + (ft_sfree(cpy) * ft_errmsg(errno)));
	new = ft_strtcat(var, cpy);
	if (!new)
		return (var + (ft_sfree(cpy) * ft_errmsg(errno)));
	return (new);
}
