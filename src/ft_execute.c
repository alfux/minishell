/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:48:07 by alfux             #+#    #+#             */
/*   Updated: 2022/08/31 18:52:39 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_execute(char **av, char ***ev, char ***var, char **his)
{
	if (ft_isbuiltin(av, ev, var, his))
	{
		if (ft_isextern(av, *ev) < 0)
		{
			ft_errmsg(errno);
			ft_sfree(his);
			ft_exit(av, *ev, *var, (char **)0);
		}
	}
}
