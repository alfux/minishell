/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 21:26:31 by alfux             #+#    #+#             */
/*   Updated: 2022/08/16 18:23:34 by alfux            ###   ########.fr       */
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
		return ((char **)(0 * (size_t)ft_errmsg(errno)));
	i = 0;
	while (*(ev + i))
	{
		*(env + i) = ft_strdup(*(ev + i));
		if (!*(env + i))
			return ((char **)(size_t)(ft_sfree(env) * ft_errmsg(errno)));
		i++;
	}
	return (env);
}
