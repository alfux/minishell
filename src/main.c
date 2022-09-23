/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:48:07 by alfux             #+#    #+#             */
/*   Updated: 2022/09/24 00:11:38 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	main(int ac, char **av, char **ev)
{
	static char	*prompt;
	static char	**cmd;
	static char	**var;
	static char	**his;
	static int	exit_status;

	ev = ft_setenv(ev, &var, &his);
	if (!ev || !ac || !av || ft_sighdl(HDL_IGNORE_SIGQUIT | HDL_IGNORE_SIGINT))
		return (ft_errmsg(errno));
	prompt = ft_prompt(ev, &his + ft_errno(0));
	while (prompt)
	{
		cmd = ft_tknize(prompt);
		(void)ft_free(prompt);
		if (cmd)
			exit_status = ft_macro_exec(cmd, &ev, &var, his);
		if (!cmd || ft_stdio(RESET_IO + ft_sfree(cmd)) || ft_exit_toggle(STATE))
			break ;
		*var = ft_extsta(exit_status, *var);
		prompt = ft_prompt(ev, &his + ft_errno(0));
	}
	if (errno && exit_status)
		(void)ft_errmsg(errno);
	ft_exit(ev, var, his);
	return (ft_errmsg(errno));
}
