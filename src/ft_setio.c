/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setio.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 04:59:20 by alfux             #+#    #+#             */
/*   Updated: 2022/09/13 05:36:50 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_setio(int cl)
{
	static int	fd_stdout;
	static int	fd_stdin;

	if (cl)
	{
		if (close(fd_stdout) == -1 || close(fd_stdin) == -1)
			return (errno);
		fd_stdout = 0;
		fd_stdin = 0;
	}
	else if (fd_stdout && fd_stdin)
	{
		if (dup2(fd_stdout, 1) == -1 || dup2(fd_stdin, 0) == -1)
			return (errno);
	}
	else
	{
		fd_stdout = dup(1);
		fd_stdin = dup(0);
		if (fd_stdout == -1 || fd_stdin == -1)
			return (errno);
	}
	return (0);
}
