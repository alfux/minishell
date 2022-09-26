/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:57:01 by alfux             #+#    #+#             */
/*   Updated: 2022/09/26 18:10:13 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_exit(char **ev, char **var, char **his)
{
	ft_sfree(ev);
	ft_sfree(var);
	if (ft_exit_toggle(STATE) != NO_SAVE_HISTORY)
		(void)ft_savhis(getenv("HOME"), HISTORY, his);
	ft_sfree(his);
	ft_stdio(CLOSE_IO);
	ft_setio(CLOSE_IO);
	exit(errno);
}
