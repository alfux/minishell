/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:48:07 by alfux             #+#    #+#             */
/*   Updated: 2022/08/29 23:13:24 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	**ft_setenv(char **ev, char ***var, char ***his)
{
	size_t	size;
	char	**addr;
	char	*buf;

	*var = (char **)0;
	*his = (char **)0;
	ev = ft_strtdup(ev);
	if (!ev)
		return ((char **)(size_t)(0 * ft_errmsg(errno)));
	addr = ft_isvarin("SHLVL=", ev);
	buf = ft_itoa(ft_atoi(*addr + 6) + 1);
	if (!buf)
		return ((char **)(size_t)(ft_sfree(ev) * ft_errmsg(errno)));
	ft_free(*addr);
	size = ft_strlen(buf);
	*addr = ft_calloc(size + 7, sizeof (char));
	ft_strlcpy(*addr, "SHLVL=", size + 7);
	ft_strlcpy(*addr + 6, buf, size + 1);
	ft_free(buf);
	return (ev);
}

int	main(int ac, char **av, char **ev)
{
	char	*prompt;
	char	**cmd;
	char	**var;
	char	**his;

	ev = ft_setenv(ev, &var, &his);
	if (!ev || !ac || !av)
		return (1);
	prompt = ft_prompt(ev, &his);
	while (prompt)
	{
		cmd = ft_cmdspl(prompt);
		ft_free(prompt);
		if (cmd)
			cmd = ft_root_parse(cmd, ev, var);
		if (cmd)
			ft_execute(cmd, &ev, &var, his);
		ft_sfree(cmd);
		prompt = ft_prompt(ev, &his);
	}
	ft_sfree(ev);
	ft_sfree(var);
	ft_sfree(his);
	//ft_savhis(".minishell_history", his);
	return (1);
}
