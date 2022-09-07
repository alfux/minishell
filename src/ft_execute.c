/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:48:07 by alfux             #+#    #+#             */
/*   Updated: 2022/09/07 04:34:11 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_inorex(char **av, char ***ev, char ***var, char **his)
{
	int		exit_status;
	pid_t	pid;

	exit_status = ft_isbuiltin(av, ev, var, his);
	if (exit_status < 0)
	{
		pid = ft_isextern(av, *ev, &ft_newpro);
		if (pid < 0)
		{
			ft_errmsg(errno);
			if (pid == -1)
			{
				(void)ft_sfree(his);
				ft_exit(av, *ev, *var, (char **)0);
			}
			else
				exit_status = errno << 8;
		}
		else
			(void)waitpid(pid, &exit_status, 0);
	}
	return (exit_status);
}

static int	ft_inorex_pipe(char **av, char ***ev, char ***var, char **his)
{
	int		exit_status;
	pid_t	pid;

	exit_status = ft_isbuiltin(av, ev, var, his);
	if (exit_status < 0)
	{
		pid = ft_isextern(av, *ev,
				(pid_t (*)(char *, char **, char **))(&execve));
		if (pid < 0)
		{
			exit_status = ft_errmsg(errno);
			if (pid == -1)
			{
				(void)ft_sfree(his);
				ft_exit(av, *ev, *var, (char **)0);
			}
		}
	}
	(void)ft_errno(exit_status);
	(void)ft_sfree(his);
	ft_exit(av, *ev, *var, (char **)0);
	return (0);
}

int	ft_execute(char **cmd, char ***ev, char ***var, char **his)
{
	pid_t	*pid;
	int		i;
	int		exit_status;

	pid = (pid_t *)0;
	cmd = ft_pipmkr(cmd, &pid);
	if (cmd == (char **)-1)
		return (1);
	if (cmd)
		cmd = ft_root_parse(cmd, *ev, *var);
	if (!pid)
		return (ft_inorex(cmd, ev, var, his));
	if (cmd)
		return (ft_inorex_pipe(cmd, ev, var, his + ft_free(pid)));
	i = 0;
	while (*(pid + i) != -1)
		(void)waitpid(*(pid + i++), &exit_status, 0);
	return (exit_status + ft_free(pid));
}
