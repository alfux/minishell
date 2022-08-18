/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_root_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:09:04 by alfux             #+#    #+#             */
/*   Updated: 2022/08/18 15:22:20 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static size_t	ft_varsze(char *arg, size_t *i, char **ev)
{
	size_t	size;
	int		j;

	j = 0;
	(*i)++;
	while (*(ev + j))
	{
		size = 0;
		while (*(*(ev + j) + size) && *(*(ev + j) + size) != '=')
			size++;
		if (!ft_strncmp(arg + *i, *(ev + j), size) && *(arg + *i + size) != '_'
			&& !ft_isalnum(*(arg + *i + size)))
		{
			*i += size - 1;
			return (ft_strlen(*(ev + j) + size + 1));
		}
		j++;
	}
	while (ft_isalnum(*(arg + *i)) || *(arg + *i) == '_')
		(*i)++;
	(*i)--;
	return (0);
}

static int	ft_newsze(char *arg, char **ev)
{
	size_t	size;
	size_t	i;
	char	quotes;
	char	dquotes;

	size = 0;
	i = 0;
	quotes = 0;
	dquotes = 0;
	while (*(arg + i))
	{
		if (!dquotes && *(arg + i) == 39)
			quotes = (quotes + 1) % 2;
		else if (!quotes && *(arg + i) == 34)
			dquotes = (dquotes + 1) % 2;
		else if (*(arg + i) == '$' && (ft_isalnum(*(arg + i + 1))
				|| *(arg + i + 1) == '_') && !quotes)
			size += ft_varsze(arg, &i, ev);
		else
			size++;
		i++;
	}
	return (size);
}

static void	ft_fill_var(char **dst, char **src, char **ev)
{
	size_t	size;
	size_t	i;
	size_t	j;

	i = 0;
	(*src)++;
	while (*(ev + i))
	{
		size = 0;
		while (*(*(ev + i) + size) && *(*(ev + i) + size) != '=')
			size++;
		if (!ft_strncmp(*src, *(ev + i), size) && !ft_isalnum(*(*src + size))
			&& *(*src + size) != '_')
		{
			*src += size - 1;
			j = 1;
			while (*(*(ev + i) + size + j))
				*((*dst)++) = *(*(ev + i) + size + j++);
			return ;
		}
		i++;
	}
	while (ft_isalnum(**src) || **src == '_')
		(*src)++;
	(*src)--;
}

static void	ft_replace(char *dst, char *src, char **ev)
{
	char	quotes;
	char	dquotes;

	quotes = 0;
	dquotes = 0;
	while (*src)
	{
		if (*src == 39 && !dquotes)
			quotes = (quotes + 1) % 2;
		else if (*src == 34 && !quotes)
			dquotes = (dquotes + 1) % 2;
		else if (*src == '$' && (ft_isalnum(*(src + 1)) || *(src + 1) == '_')
			&& !quotes)
			ft_fill_var(&dst, &src, ev);
		else
			*(dst++) = *src;
		src++;
	}
}

char	**ft_root_parse(char **cmd, char **ev)
{
	size_t	new_size;
	char	*buf;
	int		i;

	i = 0;
	while (*(cmd + i))
	{
		new_size = ft_newsze(*(cmd + i), ev);
		if (new_size >= 0)
		{
			buf = ft_calloc(new_size + 1, sizeof (char));
			if (!buf)
				return ((char **)(size_t)(ft_sfree(cmd) * ft_errmsg(errno)));
			ft_replace(buf, *(cmd + i), ev);
			free(*(cmd + i));
			*(cmd + i) = buf;
		}
		i++;
	}
	return (cmd);
}
