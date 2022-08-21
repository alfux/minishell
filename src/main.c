/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:48:07 by alfux             #+#    #+#             */
/*   Updated: 2022/08/21 01:02:32 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	main(int ac, char **av, char **ev)
{
	char	*prompt;
	char	**cmd;
	char	**var;

	var = (char **)0;
	ev = ft_envdup(ev);
	if (!ev || !ac || !av)
		return (1);
	prompt = ft_prompt(ev);
	while (prompt)
	{
		cmd = ft_root_cmdspl(prompt);
		ft_free(prompt);
		if (cmd)
			cmd = ft_root_parse(cmd, ev, var);
		ft_execute(cmd, &ev, &var);
		if (cmd)
			ft_sfree(cmd);
		prompt = ft_prompt(ev);
	}
	ft_sfree(ev);
	return (0);
}
