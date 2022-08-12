/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:48:07 by alfux             #+#    #+#             */
/*   Updated: 2022/08/12 11:04:44 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	main(int ac, char **av, char **ev)
{
	char	*prompt;
	char	**spl;
	int		child_exit_status;

	(void)ac;
	(void)av;
	ev = ft_envdup(ev);
	if (!ev)
		return (1);
	child_exit_status = 0;
	prompt = ft_prompt(ev, 0);
	//TEMP
	while (prompt && ft_strncmp(prompt, "exit", 5))
	{
		spl = ft_split(prompt, ' ');
		free(prompt);
		if (*spl && !ft_strncmp(*spl, "cd", 3))
			ft_cd(*(spl + 1), ev);
		if (*spl && !ft_strncmp(*spl, "env", 4))
			ft_env(ev);
		if (*spl && !ft_strncmp(*spl, "echo", 5))
			child_exit_status = ft_echo(spl + 1);
		ft_sfree(spl);
		prompt = ft_prompt(ev, child_exit_status);
	}
	ft_sfree(ev);
	free(prompt);
	return (0);
}
