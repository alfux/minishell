/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:48:07 by alfux             #+#    #+#             */
/*   Updated: 2022/08/11 16:03:53 by alfux            ###   ########.fr       */
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
	//TEMP
	while (prompt && ft_strncmp(prompt, "exit", 5))
	{
		spl = ft_split(prompt, ' ');
		free(prompt);
		if (*spl && !ft_strncmp(*spl, "cd", 3))
			ft_cd(*(spl + 1), ev);
		if (*spl && !ft_strncmp(*spl, "env", 4))
			ft_env(ev);
		ft_sfree(spl);
		prompt = ft_prompt(ev);
	}
	ft_sfree(ev);
	free(prompt);
	return (0);
}
