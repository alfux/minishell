/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isextern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 02:14:04 by alfux             #+#    #+#             */
/*   Updated: 2022/08/31 02:21:51 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_isextern(char **av, char **ev)
{
	if (ft_isalpha(**av))
		return (ft_errno(-4));
	else
		execve(*av, av, ev);
	return (0);
}
