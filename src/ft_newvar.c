/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:04:55 by alfux             #+#    #+#             */
/*   Updated: 2022/08/21 01:27:11 by alfux            ###   ########.fr       */
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

static int	ft_newsze(char **cmd, char **var)
{
	int	i;
	int	size;;

	i = 0;
	if (var)
		while (*(var + i))
			i++;
	size = i;
	i = 0;
	while (*(cmd + i))
	{
		if (!ft_isinvar(*(cmd + i), var))
			size++;
		i++;
	}
	return (size);
}

static char	**ft_replace(char **cmd, char **var, int tip)
{
	char	**buf;
	char	*str;

	while (*cmd)
	{
		buf = ft_isinvar(*cmd, var);
		if (buf)
		{
			str = ft_strdup(*cmd);
			if (!str)
				return ((char **)0);
			free(*buf);
			*buf = str;
		}
		else if (tip > -1)
		{
			str = ft_strdup(*cmd);
			if (!str)
				return ((char **)0);
			*(var + tip++) = str;
		}
		cmd++;
	}
	return (var);
}

static char	**ft_fillvar(char **cmd, char **var, int nsize, int vsize)
{
	char	**new;
	char	**buf;
	int		i;

	i = 0;
	if (nsize == vsize)
	{
		buf = ft_replace(cmd, var, -1);
		if (!buf)
			return ((char **)(size_t)ft_sfree(var));
		return (buf);
	}
	new = ft_calloc(nsize + 1, sizeof (char *));
	if (!new)
		return ((char **)(size_t)ft_sfree(var));
	while (var && *(var + i))
	{
		*(new + i) = *(var + i);
		i++;
	}
	buf = ft_replace(cmd, new, i);
	if (!buf)
		return ((char **)(size_t)(ft_sfree(new) * ft_free(var)));
	free(var);
	return (new);
}

char	**ft_newvar(char **cmd, char **var)
{
	char	**new;
	int		nsize;
	int		vsize;

	vsize = 0;
	if (var)
		while (*(var + vsize))
			vsize++;
	nsize = ft_newsze(cmd, var);
	new = ft_fillvar(cmd, var, nsize, vsize);
	if (!new)
		return ((char **)(size_t)(0 * ft_errmsg(errno)));
	return (new);
}
