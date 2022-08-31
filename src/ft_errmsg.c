/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errmsg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:40:11 by alfux             #+#    #+#             */
/*   Updated: 2022/08/31 18:54:03 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_errmsg_a(int errn)
{
	if (errn == -1)
		ft_putstr_fd("Error: Unclosed quotes\n", 2);
	else if (errn == -2)
		ft_putstr_fd("Error: Unclosed double quotes\n", 2);
	else if (errn == -3)
		ft_putstr_fd("Error: Couldn't find USER in environnement\n", 2);
	else if (errn == -4)
		ft_putstr_fd("Error: Couldn't find PATH in envireonnement\n", 2);
	else if (errn == -5)
		ft_putstr_fd("Error: Some personal variables may have been lost\n", 2);
	else if (errn == -6)
		ft_putstr_fd("Error: Couldn't add last command to history\n", 2);
	return (errn);
}

int	ft_errmsg(int errn)
{
	errno = errn;
	if (errn < 0)
		return (ft_errmsg_a(errn));
	else
		perror("Error");
	return (errn);
}
