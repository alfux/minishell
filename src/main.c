/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:48:07 by alfux             #+#    #+#             */
/*   Updated: 2022/08/16 18:25:41 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	main(int ac, char **av, char **ev)
{
	char	*prompt;
	char	**spl;

	(void)ac;
	(void)av;
	ev = ft_envdup(ev);
	if (!ev)
		return (1);
	prompt = ft_prompt(ev);
	while (prompt && ft_strncmp(prompt, "exit", 5))
	{
		spl = ft_cmdspl(prompt);
		free(prompt);
		if (spl && *spl && !ft_strncmp(*spl, "cd", 3))
			ft_cd(spl, ev);
		if (spl && *spl && !ft_strncmp(*spl, "env", 4))
			ft_env(ev);
		if (spl && *spl && !ft_strncmp(*spl, "echo", 5))
			ft_echo(spl);
		if (spl)
			ft_sfree(spl);
		prompt = ft_prompt(ev);
	}
	ft_sfree(ev);
	free(prompt);
	return (0);
}
