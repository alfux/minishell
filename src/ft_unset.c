/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 16:20:04 by alfux             #+#    #+#             */
/*   Updated: 2022/08/26 10:38:16 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_unset(char **av, char ***ev, char ***var)
{
	char	**buf;
	int		i;

	i = 0;
	while (*(av + i))
	{
		buf = ft_isvarin(*(av + i), *var);
		if (buf)
		{
			if (ft_strtdelone(buf, var))
				return (ft_errmsg(errno));
		}
		else
		{
			buf = ft_isvarin(*(av + i), *ev);
			if (buf && ft_strtdelone(buf, ev))
				return (ft_errmsg(errno));
		}
		i++;
	}
	return (0);
}
