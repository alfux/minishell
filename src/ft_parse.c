/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 14:22:52 by alfux             #+#    #+#             */
/*   Updated: 2022/08/14 20:23:55 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static size_t	ft_sizeof_vev(char *vev, char **ev)
{
	size_t	i;
	size_t	size;

	i = 0;
	while (*(ev + i))
	{
		size = 0;
		while (*(*(ev + i) + size) && *(*(ev + i) + size) != '=')
			size++;
		if (!ft_strncmp(vev, *(ev + i), size) && !ft_isalnum(*(vev + size))
			&& *(vev + size) != '_')
			return (ft_strlen(*(ev + i) + size + 1));
		i++;
	}
	return (0);
}

static size_t	ft_post_size(char *pmt, char **ev)
{
	size_t	size;
	char	dquote;
	char	quote;
	size_t	i;

	size = 1;
	dquote = 0;
	quote = 0;
	i = 0;
	while (*(pmt + i))
	{
		if (!dquote && *(pmt + i) == 39)
			quote = (quote + 1) % 2;
		else if (!quote && *(pmt + i) == 34)
			dquote = (dquote + 1) % 2;
		else if (!quote && *(pmt + i) == '$' && *(pmt + i + 1) != ' ')
			size += ft_sizeof_vev(pmt + i + 1, ev);
		else
			size++;
		i++;
	}
	if (dquote || quote)
		return (0);
	return (size);
}

char	**ft_parse(char *pmt, char **ev)
{
	size_t	size;
	char	*parsed;
	char	**spl;

	size = ft_post_size(pmt, ev);
	if (!size)
		return ((char **)(0 * (size_t)ft_printf(
				"Syntax: quotes or double quotes are not correctly closed\n")));
	parsed = ft_calloc(size, sizeof (char));
	if (!parsed)
		return ((char **)(0 * (size_t)ft_errmsg(errno)));
	spl = ft_split(parsed, ' ');
	free(parsed);
	if (!spl)
		return ((char **)(0 * (size_t)ft_errmsg(errno)));
	return (spl);
}
