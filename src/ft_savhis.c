/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_savhis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 21:20:17 by alfux             #+#    #+#             */
/*   Updated: 2022/08/30 19:34:51 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_savhis(char *fname, char **his)
{
	int	fd;

	fd = open(fname, O_WRONLY | O_CREAT | O_APPEND, 0000600);
	if (fd == -1)
		return (ft_errmsg(errno));
	while (*his)
	{
		ft_putstr_fd(*(his++), fd);
		ft_putchar_fd('\n', fd);
	}
	if (close(fd) == -1)
		return (ft_errmsg(errno));
	return (0);
}
