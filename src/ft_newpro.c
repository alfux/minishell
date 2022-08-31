/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newpro.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 12:53:59 by alfux             #+#    #+#             */
/*   Updated: 2022/08/31 14:00:44 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_newpro(char *path, char **av, char **ev)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (!pid)
		return (execve(path, av, ev));
	(void)waitpid(pid, &status, 0);
	return (status);
}
