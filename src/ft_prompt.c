/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 03:55:37 by alfux             #+#    #+#             */
/*   Updated: 2022/08/11 15:51:05 by alfux            ###   ########.fr       */
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
	{
		ft_errmsg(errno + ft_free(path));
		return ((char *)0);
	}
	ft_strlcpy(dir, "\033[33m", i - j + 14);
	ft_strlcpy(dir + 5, path + j, i - j + 9);
	free(path);
	ft_strlcpy(dir + i - j + 5, " -> ", 9);
	ft_strlcpy(dir + i - j + 9, "\033[0m", 5);
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
	*ret = '\0';
	return (ret);
}
