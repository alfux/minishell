/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:57:01 by alfux             #+#    #+#             */
/*   Updated: 2022/09/01 03:01:53 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_exit(char **av, char **ev, char **var, char **his)
{
	ft_sfree(av);
	ft_sfree(ev);
	ft_sfree(var);
	if (his)
		(void)ft_savhis(getenv("HOME"), HISTORY, his);
	ft_sfree(his);
	exit(0);
}
