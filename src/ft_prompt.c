/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 03:55:37 by alfux             #+#    #+#             */
/*   Updated: 2022/08/12 14:03:09 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*ft_color_directory(void)
{
	char	*path;
	char	*dir;
	int		i;
	int		j;

	path = ft_newpwd();
	if (!path)
		return ((void *)0);
	i = 0;
	j = 0;
	while (*(path + i))
		if (*(path + i++) == '/')
			j = i;
	dir = ft_calloc(i - j + 14, sizeof (char));
	if (!dir)
		return ((char *)(0 * (size_t)ft_errmsg(errno + ft_free(path))));
	ft_strlcat(dir, "\033[33m", i - j + 14);
	ft_strlcat(dir, path + j, i - j + 14);
	free(path);
	ft_strlcat(dir, " -> ", i - j + 14);
	ft_strlcat(dir, "\033[0m", i - j + 14);
	return (dir);
}

char	*ft_prompt(char **ev)
{
	char	*dir;
	char	*ret;

	(void)ev;
	dir = ft_color_directory();
	if (!dir)
		return ((void *)0);
	ret = readline(dir);
	free(dir);
	if (ret)
		return (ret);
	ret = ft_calloc(1, sizeof (char));
	if (!ret)
		return ((void *)0);
	*ret = '\0';
	return (ret);
}
