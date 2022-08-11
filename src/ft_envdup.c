/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 21:26:31 by alfux             #+#    #+#             */
/*   Updated: 2022/08/11 15:53:08 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**ft_envdup(char **ev)
{
	char	**env;
	int		i;

	i = 0;
	while (*(ev + i))
		i++;
	env = ft_calloc(i + 1, sizeof (char *));
	if (!env)
	{
		ft_errmsg(errno);
		return ((char **)0);
	}
	i = 0;
	while (*(ev + i))
	{
		*(env + i) = ft_strdup(*(ev + i));
		if (!*(env + i))
		{
			ft_errmsg(errno);
			ft_sfree(env);
			return ((char **)0);
		}
		i++;
	}
	return (env);
}
