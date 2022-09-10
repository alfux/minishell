/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:48:07 by alfux             #+#    #+#             */
/*   Updated: 2022/09/10 14:28:31 by alfux            ###   ########.fr       */
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
				ft_exit(av, *ev, *var, (char **)(size_t)ft_sfree(his));
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
				ft_exit(av, *ev, *var, (char **)(size_t)ft_sfree(his));
		}
	}
	(void)ft_errno(exit_status);
	ft_exit(av, *ev, *var, (char **)(size_t)ft_sfree(his));
	return (0);
}

static int	ft_one_cmd(char	**av, char ***ev, char ***var, char **his)
{
	if (ft_root_parse(av, *ev, *var))
		return (errno);
	return (ft_inorex(av, ev, var, his));
}

static int	ft_frk_cmd(char	**av, char ***ev, char ***var, char **his)
{
	if (ft_root_parse(av, *ev, *var))
		ft_exit(av, *ev, *var, (char **)(size_t)ft_sfree(his));
	return (ft_inorex_pipe(av, ev, var, his));
}

int	ft_execute(char **av, char ***ev, char ***var, char **his)
{
	pid_t	*pid;
	char	**cmd;
	int		i;
	int		exit_status;

	pid = (pid_t *)0;
	cmd = ft_pipmkr(av, &pid);
	if (cmd == (char **)-1)
		return (errno);
	if (!pid)
		return (ft_one_cmd(cmd, ev, var, his));
	if (cmd)
		return (ft_frk_cmd(cmd, ev, var, his + ft_free(pid) + ft_sfree(av)));
	i = 0;
	while (*(pid + i))
		(void)waitpid(*(pid + i++), &exit_status, 0);
	return (exit_status + ft_free(pid));
}
