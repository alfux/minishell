/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setio.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 04:59:20 by alfux             #+#    #+#             */
/*   Updated: 2022/09/16 18:10:06 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_reseti(void)
{
	int	fd;

	fd = dup(1);
	if (fd == -1)
		return (-1);
	if (ft_setio(RESET_IO))
		return (-1);
	if (dup2(fd, 1) == -1)
		return (-1);
	return (0);
}

int	ft_setio(int flag)
{
	static int	fd_stdout;
	static int	fd_stdin;

	if (!fd_stdout && !fd_stdin)
	{
		fd_stdout = dup(1);
		fd_stdin = dup(0);
		if (fd_stdout == -1 || fd_stdin == -1)
			return (-1);
	}
	else if (flag == CLOSE_IO)
	{
		if (close(fd_stdout) == -1 || close(fd_stdin) == -1)
			return (-1);
		fd_stdout = 0;
		fd_stdin = 0;
	}
	else if (flag == RESET_IN)
		return (ft_reseti());
	else if (flag == RESET_IO)
	{
		if (dup2(fd_stdout, 1) == -1 || dup2(fd_stdin, 0) == -1)
			return (-1);
	}
	return (0);
}
