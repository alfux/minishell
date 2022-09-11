/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbuiltin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:48:07 by alfux             #+#    #+#             */
/*   Updated: 2022/09/07 04:13:39 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_check_for_var(char **cmd, char ***ev, char ***var, char **his)
{
	int	check;

	check = ft_isntvar(cmd);
	if (check > 1)
		return (ft_isbuiltin(cmd + check - 1, ev, var, his));
	else if (check)
		return (-1);
	return (ft_setvar(cmd, *ev, var) << 8);
}

int	ft_isbuiltin(char **cmd, char ***ev, char ***var, char **his)
{
	int	exit_status;

	exit_status = 0;
	if (cmd && *cmd && !ft_strncmp(*cmd, "cd", 3))
		exit_status = ft_cd(cmd, ev);
	else if (cmd && *cmd && !ft_strncmp(*cmd, "env", 4))
		exit_status = ft_env(*ev);
	else if (cmd && *cmd && !ft_strncmp(*cmd, "echo", 5))
		exit_status = ft_echo(cmd);
	else if (cmd && *cmd && !ft_strncmp(*cmd, "pwd", 4))
		exit_status = ft_pwd();
	else if (cmd && *cmd && !ft_strncmp(*cmd, "exit", 5))
		ft_exit(cmd, *ev, *var, his);
	else if (cmd && *cmd && !ft_strncmp(*cmd, "export", 7))
		exit_status = ft_export(cmd, ev, var);
	else if (cmd && *cmd && !ft_strncmp(*cmd, "unset", 6))
		exit_status = ft_unset(cmd, ev, var);
	else
		return (ft_check_for_var(cmd, ev, var, his));
	return (exit_status << 8);
}
