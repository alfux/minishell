/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:04:04 by alfux             #+#    #+#             */
/*   Updated: 2022/08/16 14:29:46 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	ft_shwarg(char **av, char opt)
{
	int	i;

	i = opt;
	while (*(av + i))
	{
		ft_printf("%s", *(av + i++));
		if (*(av + i))
			ft_printf(" ");
		else if (!opt)
			ft_printf("\n");
	}
}

int	ft_echo(char **av)
{
	if (!av || !*av)
		return (0 * ft_printf("\n"));
	av++;
	if (!ft_strncmp(*av, "-n", 3))
	{
		ft_shwarg(av, 1);
		return (1);
	}
	ft_shwarg(av, 0);
	return (0);
}
