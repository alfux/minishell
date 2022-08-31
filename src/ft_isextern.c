/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isextern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 02:14:04 by alfux             #+#    #+#             */
/*   Updated: 2022/08/31 16:08:21 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_isextern(char **av, char **ev)
{
	if (ft_isalnum(**av))
		return (0 * ft_errmsg(-4));
	else
		return (ft_newpro(*av, av, ev));
}
