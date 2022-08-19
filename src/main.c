/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:48:07 by alfux             #+#    #+#             */
/*   Updated: 2022/08/19 14:56:52 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	ft_choose(char **spl, char **ev)
{
	if (spl && *spl && !ft_strncmp(*spl, "cd", 3))
		ft_cd(spl, ev);
	if (spl && *spl && !ft_strncmp(*spl, "env", 4))
		ft_env(ev);
	if (spl && *spl && !ft_strncmp(*spl, "echo", 5))
		ft_echo(spl);
	if (spl && *spl && !ft_strncmp(*spl, "pwd", 4))
		ft_pwd();
	if (spl && *spl && !ft_strncmp(*spl, "exit", 5))
		ft_exit(spl, ev);
}

int	main(int ac, char **av, char **ev)
{
	char	*prompt;
	char	**spl;

	ev = ft_envdup(ev);
	if (!ev || !ac || !av)
		return (1);
	prompt = ft_prompt(ev);
	while (prompt)
	{
		spl = ft_root_cmdspl(prompt);
		ft_free(prompt);
		if (spl)
			spl = ft_root_parse(spl, ev);
		ft_choose(spl, ev);
		if (spl)
			ft_sfree(spl);
		prompt = ft_prompt(ev);
	}
	ft_sfree(ev);
	return (0);
}
