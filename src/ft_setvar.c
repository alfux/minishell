/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:04:55 by alfux             #+#    #+#             */
/*   Updated: 2022/08/25 17:17:09 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_replace(char **av, char **ev, char **var, char **add)
{
	char	**buf;
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (*(av + i))
	{
		str = ft_strdup(*(av + i++));
		if (!str)
			return (1);
		buf = ft_isvarin(str, ev);
		if (buf)
			*buf = str + ft_free(*buf);
		else
		{
			buf = ft_isvarin(str, var);
			if (buf)
				*buf = str + ft_free(*buf);
			else
				*(add + j++) = str;
		}
	}
	return (0);
}

static char	**ft_rm_dup(char **av)
{
	char	**new;
	char	**buf;
	int		i;
	int		j;

	new = ft_calloc(ft_strtlen(av) + 1, sizeof (char *));
	if (!new)
		return ((char **)0);
	i = 0;
	j = 0;
	while (*(av + i))
	{
		buf = ft_isvarin(*(av + i), new);
		if (buf)
			*buf = *(av + i);
		else
			*(new + j++) = *(av + i);
		i++;
	}
	return (new);
}

char	**ft_setvar(char **av, char **ev, char **var)
{
	char	**add;
	char	**new;

	if (!var)
		var = ft_calloc(1, sizeof (char *));
	if (!var)
		return (var + (0 * ft_errmsg(errno)));
	av = ft_rm_dup(av);
	if (!av)
		return (var + (0 * ft_errmsg(errno)));
	add = ft_calloc(ft_strtlen(av) + 1, sizeof (char *));
	if (!add)
		return (var + (ft_free(av) * ft_errmsg(errno)));
	if (ft_replace(av, ev, var, add))
		return (var + (ft_free(av) * ft_sfree(add) * ft_errmsg(errno)));
	ft_free(av);
	new = ft_strtcat(var, add);
	if (!new)
		return (var + (ft_sfree(add) * ft_errmsg(errno)));
	ft_free(var);
	ft_free(add);
	return (new);
}
