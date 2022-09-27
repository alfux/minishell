/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:18:37 by alfux             #+#    #+#             */
/*   Updated: 2022/09/23 18:35:05 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_trace(char *file, char **av)
{
	int	fd;
	int	i;

	i = 0;
	fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0000644);
	while (*(av + i))
	{
		ft_putstr_fd("\"", fd);
		ft_putstr_fd(*(av + i++), fd);
		ft_putstr_fd("\"", fd);
		ft_putstr_fd("\n", fd);
	}
	close(fd);
}
