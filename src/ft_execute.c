/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:48:07 by alfux             #+#    #+#             */
/*   Updated: 2022/08/19 18:35:57 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_execute(char **cmd, char ***ev, char ***var)
{
	if (ft_isbuiltin(cmd, ev, var))
		return ;
	else if (ft_isexternal(cmd, ev, var))
		return ;
	else
		ft_errmsg(-4);
}
