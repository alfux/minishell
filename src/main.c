/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:48:07 by alfux             #+#    #+#             */
/*   Updated: 2022/09/22 17:58:38 by alfux            ###   ########.fr       */
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
			exit_status = ft_execute(cmd, &ev, &var, his);
		*var = ft_extsta(exit_status, *var);
		if (!cmd || ft_setio(RESET_IO + ft_sfree(cmd)))
			break ;
		prompt = ft_prompt(ev, &his + ft_errno(0));
	}
	if (errno)
		(void)ft_errmsg(errno);
	ft_exit((char **)0, ev, var, his);
	return (ft_errmsg(errno));
}
