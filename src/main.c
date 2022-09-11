/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:48:07 by alfux             #+#    #+#             */
/*   Updated: 2022/09/11 14:45:48 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	main(int ac, char **av, char **ev)
{
	char	*prompt;
	char	**cmd;
	char	**var;
	char	**his;
	int		exit_status;

	ev = ft_setenv(ev, &var, &his);
	if (!ev || !ac || !av)
		return (ft_errmsg(errno));
	prompt = ft_prompt(ev, &his);
	while (prompt)
	{
		cmd = ft_cmdspl(prompt);
		ft_free(prompt);
		if (cmd)
			exit_status = ft_execute(cmd, &ev, &var, his) >> 8;
		*var = ft_extsta(exit_status, *var);
		ft_sfree(cmd);
		prompt = ft_prompt(ev, &his);
	}
	ft_sfree(ev);
	ft_sfree(var);
	(void)ft_savhis(getenv("HOME"), HISTORY, his);
	ft_sfree(his);
	return (ft_errmsg(errno));
}
