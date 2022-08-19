/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_root_cmdspl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:10:20 by alfux             #+#    #+#             */
/*   Updated: 2022/08/19 02:21:51 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static size_t	ft_arglen(char *arg)
{
	size_t	i;
	char	quote;
	char	dquote;

	i = 0;
	quote = 0;
	dquote = 0;
	while (*(arg + i) && !(*(arg + i) == ' ' && !quote && !dquote))
	{
		if (!quote && *(arg + i) == 34)
			dquote = (dquote + 1) % 2;
		else if (!dquote && *(arg + i) == 39)
			quote = (quote + 1) % 2;
		i++;
	}
	if (quote)
		return (-1);
	if (dquote)
		return (-2);
	return (i);
}

static int	ft_argcnt(char *cmd)
{
	int		argc;
	size_t	argl;
	size_t	i;

	i = 0;
	argc = 0;
	while (*(cmd + i))
	{
		while (*(cmd + i) == ' ')
			i++;
		if (*(cmd + i))
			argc++;
		argl = ft_arglen(cmd + i);
		if (argl == (size_t)(-1))
			return (-1);
		else if (argl == (size_t)(-2))
			return (-2);
		i += argl;
	}
	return (argc);
}

char	**ft_root_cmdspl(char *cmd)
{
	char	**spl;
	int		argc;
	int		argl;
	int		i;
	size_t	j;

	argc = ft_argcnt(cmd);
	if (argc < 0)
		return ((char **)(0 * (size_t)ft_errmsg(argc)));
	spl = ft_calloc(argc + 1, sizeof (char *));
	if (!spl)
		return ((char **)(0 * (size_t)ft_errmsg(errno)));
	i = 0;
	j = 0;
	while (i < argc)
	{
		while (*(cmd + j) == ' ')
			j++;
		argl = ft_arglen(cmd + j);
		*(spl + i) = ft_substr(cmd, j, argl);
		if (!*(spl + i++))
			return ((char **)(0 * (size_t)(ft_sfree(spl) * ft_errmsg(errno))));
		j += argl;
	}
	return (spl);
}
