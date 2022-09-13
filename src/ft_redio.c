/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redio.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 20:38:27 by alfux             #+#    #+#             */
/*   Updated: 2022/09/13 06:03:49 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_shift(char **av, int len)
{
	int	size;
	int	i;

	size = ft_strtlen(av);
	if (len > size)
		return (1);
	i = 0;
	while (i < len)
		ft_free(*(av + i++));
	i = 0;
	while (i + len < size)
	{
		*(av + i) = *(av + i + len);
		i++;
	}
	while (i < size)
		*(av + i++) = (char *)0;
	return (0);
}

static int	ft_redout(char **av, char **ev, char **var)
{
	char	**fname;
	int		fd;
	int		i;

	i = 0;
	while (*(av + i))
	{
		if (!ft_strncmp(*(av + i), ">", 2) || !ft_strncmp(*(av + i), ">>", 3))
		{
			fname = ft_substrt(av, i + 1, 1);
			if (!fname || ft_root_parse(fname, ev, var))
				return (errno);
			if (*(*(av + i) + 1))
				fd = open(*fname, O_CREAT | O_WRONLY | O_APPEND, 0000664);
			else
				fd = open(*fname, O_CREAT | O_WRONLY | O_TRUNC, 0000664);
			if (fd == -1 || dup2(fd, 1) == -1 || close(fd) == -1)
				return (errno + ft_sfree(fname));
			(void)ft_sfree(fname);
			(void)ft_shift(av + i, 2);
		}
		else
			i++;
	}
	return (0);
}

static int	ft_redin(char **av, char **ev, char **var)
{
	(void)av;
	(void)ev;
	(void)var;
	return (0);
}

int	ft_redio(char **av, char **ev, char **var)
{
	if (ft_redout(av, ev, var))
		return (errno);
	if (ft_redin(av, ev, var))
		return (errno);
	return (0);
}
