/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:48:07 by alfux             #+#    #+#             */
/*   Updated: 2022/09/06 11:39:36 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	ft_inorex(char **av, char ***ev, char ***var, char **his)
{
	if (ft_isbuiltin(av, ev, var, his))
	{
		if (ft_isextern(av, *ev) < 0)
		{
			ft_errmsg(errno);
			ft_sfree(his);
			ft_exit(av, *ev, *var, (char **)0);
		}
	}
}

int	ft_execute(char **cmd, char ***ev, char ***var, char **his)
{
	pid_t	*pid;
	int		i;

	pid = (pid_t *)0;
	i = 0;
	cmd = ft_pipmkr(cmd, &pid);
	if (cmd == (char **)-1)
		return (1);
	else if (cmd)
	{
		cmd = ft_root_parse(cmd, *ev, *var);
		if (cmd)
			ft_inorex(cmd, ev, var, his);
		if (pid)
			ft_exit(cmd, *ev, *var,
				(char **)(size_t)(ft_sfree(his) + ft_free(pid)));
	}
	else
		while (*(pid + i) != -1)
			waitpid(*(pid + i++), (int *)0, 0);
	return (ft_free(pid));
}
