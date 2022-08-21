/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbuiltin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:48:07 by alfux             #+#    #+#             */
/*   Updated: 2022/08/21 02:27:43 by alfux            ###   ########.fr       */
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
			if (((!ft_isalnum(*(*(cmd + i) + j)) && *(*(cmd + i) + j) != '_'))
				|| !*(*(cmd + i) + j + 1))
			{
				if (j > 0 && *(*(cmd + i) + j) && *(*(cmd + i) + j) == '=')
					break ;
				else
					return (i + 1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_isbuiltin(char **cmd, char ***ev, char ***var)
{
	int	ret;

	if (cmd && *cmd && !ft_strncmp(*cmd, "cd", 3))
		ft_cd(cmd, *ev);
	else if (cmd && *cmd && !ft_strncmp(*cmd, "env", 4))
		ft_env(*ev);
	else if (cmd && *cmd && !ft_strncmp(*cmd, "echo", 5))
		ft_echo(cmd);
	else if (cmd && *cmd && !ft_strncmp(*cmd, "pwd", 4))
		ft_pwd();
	else if (cmd && *cmd && !ft_strncmp(*cmd, "exit", 5))
		ft_exit(cmd, *ev);
	else
	{
		ret = ft_isntvar(cmd);
		if (ret > 1)
			return (ft_isbuiltin(cmd + ret - 1, ev, var));
		else if (ret)
			return (0);
		*var = ft_newvar(cmd, *var);
		if (!*var)
			ft_putstr_fd("Lack of memory: non-env variables deleted\n", 2);
	}
	return (1);
}
