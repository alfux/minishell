/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 03:55:37 by alfux             #+#    #+#             */
/*   Updated: 2022/08/23 16:05:43 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*ft_addusr(char **ev, char *dir, int size)
{
	char	*usr;
	size_t	usize;
	int		i;

	i = 0;
	while (*(ev + i))
	{
		if (!ft_strncmp(*(ev + i), "USER=", 5))
		{
			usize = ft_strlen(*(ev + i) + 5);
			usr = ft_calloc(usize + size + 20, sizeof (char));
			if (!usr)
				return ((char *)(size_t)(ft_free(dir) * ft_errmsg(errno)));
			ft_strlcat(usr, "\033[32m", usize + size + 20);
			ft_strlcat(usr, *(ev + i) + 5, usize + size + 20);
			ft_strlcat(usr, "@minishell \033[0m", usize + size + 20);
			ft_strlcat(usr, dir, usize + size + 20);
			return (usr + ft_free(dir));
		}
		i++;
	}
	return ((char *)(size_t)(ft_free(dir) * ft_errmsg(-3)));
}

static char	*ft_color_prompt(char **ev)
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
		return ((char *)(size_t)(ft_errmsg(errno) * ft_free(path)));
	ft_strlcat(dir, "\033[33m", i - j + 14);
	ft_strlcat(dir, path + j, i - j + 14);
	free(path);
	ft_strlcat(dir, " -> ", i - j + 14);
	ft_strlcat(dir, "\033[0m", i - j + 14);
	return (ft_addusr(ev, dir, i - j + 14));
}

char	*ft_prompt(char **ev)
{
	char	*pmt;
	char	*ret;

	pmt = ft_color_prompt(ev);
	if (!pmt)
		return ((void *)0);
	ret = readline(pmt);
	free(pmt);
	if (ret)
		return (ret);
	ret = ft_calloc(1, sizeof (char));
	if (!ret)
		return ((void *)(0 * (size_t)ft_errmsg(errno)));
	*ret = '\0';
	return (ret);
}
