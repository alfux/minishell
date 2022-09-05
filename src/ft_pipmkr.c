/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipmkr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:02:01 by alfux             #+#    #+#             */
/*   Updated: 2022/09/06 00:40:23 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	**ft_pipfrk(char **cmd, pid_t *pid, int *fd, int *prev_fd)
{
	*pid = fork();
	if (*pid)
		return ((char **)(size_t)ft_sfree(cmd));
	if (prev_fd)
		(void)dup2(prev_fd[0], 0);
	if (fd)
		(void)dup2(fd[1], 1);
	return (cmd);
}

static char	**ft_pipmkr_rec(char **av, pid_t *pid, int *prev_fd)
{
	char	**cmd;
	char	**nxt;
	int		fd[2];
	int		i;

	i = 0;
	while (*(av + i) && ft_strncmp(*(av + i), "|", 2))
		i++;
	cmd = ft_substrt(av, 0, i);
	if (!cmd)
		return ((char **)-1);
	if (*(av + i))
	{
		pipe(fd);
		nxt = ft_pipmkr_rec(av + i + 1, pid + 1, fd);
		if (nxt)
			return (nxt + (ft_sfree(cmd) * close(fd[0]) * close(fd[1])));
		nxt = ft_pipfrk(cmd, pid, fd, prev_fd);
		return (nxt + (0 * close(fd[0]) * close(fd[1])));
	}
	return (ft_pipfrk(cmd, pid, (int *)0, prev_fd));
}

char	**ft_pipmkr(char **av, pid_t **pid)
{
	int		i;
	int		j;
	char	**buf;

	i = 0;
	j = 0;
	while (*(av + i))
	{
		if (!ft_strncmp(*(av + i), "|", 2))
			j++;
		i++;
	}
	if (j > 0)
	{
		*pid = ft_calloc(j + 2, sizeof (pid_t));
		*(*pid + j + 1) = -1;
	}
	else
		return (av);
	buf = ft_pipmkr_rec(av, *pid, (int *)0);
	if (buf == (char **)-1)
		return ((char **)-1 + (0 * ft_errmsg(errno)));
	if (buf)
		ft_sfree(av);
	return (buf);
}
