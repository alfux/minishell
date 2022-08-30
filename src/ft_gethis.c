/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gethis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 19:28:46 by alfux             #+#    #+#             */
/*   Updated: 2022/08/30 21:39:59 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_gethis(char *fname)
{
	size_t	size;
	char	*line;
	int		fd;

	fd = open(fname, O_RDONLY | O_CREAT, 0000600);
	if (fd == -1)
		return (errno);
	line = get_next_line(fd + ft_errno(0));
	if (!line && errno)
		return (errno + (0 * close(fd)));
	while (line)
	{
		size = ft_strlen(line);
		if (*(line + size - 1) == '\n')
			*(line + size - 1) = '\0';
		add_history(line);
		free(line);
		line = get_next_line(fd + ft_errno(0));
		if (!line && errno)
			return (errno + (0 * close(fd)));
	}
	return (close(fd) * (-1) * errno);
}
