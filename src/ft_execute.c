/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:48:07 by alfux             #+#    #+#             */
/*   Updated: 2022/08/31 16:07:35 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_execute(char **av, char ***ev, char ***var, char **his)
{
	if (ft_isbuiltin(av, ev, var, his))
		if (ft_isextern(av, *ev) < 0)
			ft_exit(av, *ev, *var,
				(char **)(size_t)(ft_sfree(his) * ft_errmsg(errno)));
}
