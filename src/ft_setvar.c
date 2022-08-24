/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:04:55 by alfux             #+#    #+#             */
/*   Updated: 2022/08/24 14:22:58 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	**ft_isinvar(char *candidate, char **ev, char **var)
{
	size_t	size;
	int		i;

	if (!var || !*var)
		return ((char **)0);
	size = 0;
	while (*(candidate + size) && *(candidate + size) != '=')
		size++;
	i = 0;
	while (ev && *(ev + i))
	{
		if (!ft_strncmp(candidate, *(ev + i), size + 1))
			return (ev + i);
		i++;
	}
	i = 0;
	while (*(var + i))
	{
		if (!ft_strncmp(candidate, *(var + i), size + 1))
			return (var + i);
		i++;
	}
	return ((char **)0);
}

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
		str = ft_strdup(*(av + i));
		if (!str)
			return (1);
		buf = ft_isinvar(str, ev, var);
		if (buf)
		{
			free(*buf);
			*buf = str;
		}
		else
			*(add + j++) = str;
		i++;
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
		buf = ft_isinvar(*(av + i), (char **)0, new);
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
	return (new);
}
