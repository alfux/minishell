/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newpro.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 12:53:59 by alfux             #+#    #+#             */
/*   Updated: 2022/09/19 17:38:04 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

pid_t	ft_newpro(char *path, char **av, char **ev)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		if (ft_sighdl(HDL_REINIT_SIGQUIT | HDL_REINIT_SIGINT))
			return (-1);
		return (execve(path, av, ev));
	}
	return (pid);
}
