/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbuiltin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:48:07 by alfux             #+#    #+#             */
/*   Updated: 2022/08/24 14:24:51 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_isntvar(char **cmd)
{
	size_t	j;
	int		i;

	if (!cmd)
		return (1);
	i = 0;
	while (*(cmd + i))
	{
		j = 0;
		while (*(*(cmd + i) + j))
		{
			if ((!ft_isalnum(*(*(cmd + i) + j)) && *(*(cmd + i) + j) != '_')
				|| !*(*(cmd + i) + j + 1))
			{
				if (j > 0 && *(*(cmd + i) + j) == '=')
					break ;
				return (i + 1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static int	ft_check_for_var(char **cmd, char ***ev, char ***var)
{
	int	check;

	check = ft_isntvar(cmd);
	if (check > 1)
		return (ft_isbuiltin(cmd + check - 1, ev, var));
	else if (check)
		return (0);
	*var = ft_setvar(cmd, *ev, *var);
	return (1);
}

int	ft_isbuiltin(char **cmd, char ***ev, char ***var)
{
	if (cmd && *cmd && !ft_strncmp(*cmd, "cd", 3))
		*ev = ft_cd(cmd, *ev);
	else if (cmd && *cmd && !ft_strncmp(*cmd, "env", 4))
		ft_env(*ev);
	else if (cmd && *cmd && !ft_strncmp(*cmd, "echo", 5))
		ft_echo(cmd);
	else if (cmd && *cmd && !ft_strncmp(*cmd, "pwd", 4))
		ft_pwd();
	else if (cmd && *cmd && !ft_strncmp(*cmd, "exit", 5))
		ft_exit(cmd, *ev, *var);
	else
		return (ft_check_for_var(cmd, ev, var));
	return (1);
}
