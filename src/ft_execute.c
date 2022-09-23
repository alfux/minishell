/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:48:07 by alfux             #+#    #+#             */
/*   Updated: 2022/09/24 00:34:42 by alfux            ###   ########.fr       */
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
			if (pid == -1)
				(void)ft_exit_toggle(NO_SAVE_HISTORY);
			else
				exit_status = ft_errmsg(errno);
		}
		else
			(void)ft_waitall(0, &exit_status, 0);
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
			exit_status = errno;
	}
	(void)ft_errno(exit_status);
	(void)ft_exit_toggle(NO_SAVE_HISTORY);
	return (exit_status);
}

static int	ft_one_cmd(char	**av, char ***ev, char ***var, char **his)
{
	if (ft_setio(SAVE_IO) == -1)
		return (errno);
	if (ft_redio(av, *ev, *var) && 1 + ft_errmsg(errno))
		return (errno);
	if (*av && !ft_strncmp(*av, "(", 2))
		return (ft_macro_exec(ft_remout(av), ev, var, his));
	if (ft_root_parse(av, *ev, *var) && 1 + ft_errmsg(errno))
		return (errno);
	return (ft_inorex(av, ev, var, his));
}

static int	ft_frk_cmd(char	**av, char ***ev, char ***var, char **his)
{
	int	exit_status;

	if (ft_setio(SAVE_IO) == -1)
		return (errno + (0 * ft_exit_toggle(NO_SAVE_HISTORY)));
	if (ft_redio(av, *ev, *var) && 1 + ft_errmsg(errno))
		return (errno + (0 * ft_exit_toggle(NO_SAVE_HISTORY)));
	if (*av && !ft_strncmp(*av, "(", 2))
	{
		exit_status = ft_macro_exec(ft_remout(av), ev, var, his);
		return (exit_status + (0 * ft_exit_toggle(NO_SAVE_HISTORY)));
	}
	if (ft_root_parse(av, *ev, *var) && 1 + ft_errmsg(errno))
		return (errno + (0 * ft_exit_toggle(NO_SAVE_HISTORY)));
	return (ft_inorex_pipe(av, ev, var, his));
}

int	ft_execute(char **av, char ***ev, char ***var, char **his)
{
	pid_t	*pid;
	char	**cmd;
	int		exit_stat;

	pid = (pid_t *)0;
	cmd = ft_pipmkr(av, &pid);
	if (cmd == (char **)-1)
	{
		if (!pid)
			return (ft_errmsg(errno));
		if (!*pid && !ft_free(pid) + ft_errmsg(errno))
			return (ft_exit_toggle(NO_SAVE_HISTORY));
		exit_stat = ft_errmsg(errno);
		(void)ft_waitall(pid, (int *)0, 0);
		return (exit_stat + ft_free(pid));
	}
	if (!pid)
		return (ft_one_cmd(cmd, ev, var, his));
	if (cmd)
		return (ft_frk_cmd(cmd, ev, var, his + ft_free(pid) + ft_sfree(av)));
	(void)ft_waitall(pid, &exit_stat, 0);
	return (exit_stat + ft_free(pid));
}
