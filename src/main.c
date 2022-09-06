/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:48:07 by alfux             #+#    #+#             */
/*   Updated: 2022/09/06 18:05:33 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	**ft_setenv(char **ev, char ***var, char ***his)
{
	size_t	size;
	char	**addr;
	char	*buf;

	*var = ft_init_var();
	if (!*var)
		return ((char **)0);
	*his = ft_calloc(1, sizeof (char *));
	if (!*his)
		return ((char **)(size_t)ft_sfree(*var));
	if (ft_gethis(getenv("HOME"), HISTORY))
		ft_errmsg(-8 + (0 * ft_errmsg(errno)));
	ev = ft_strtdup(ev);
	if (!ev)
		return ((char **)(size_t)(ft_sfree(*his) * ft_sfree(*var)));
	addr = ft_isvarin("SHLVL=", ev);
	buf = ft_itoa(ft_atoi(*addr + 6) + 1);
	if (!buf)
		return ((char **)(size_t)(ft_sfree(*his) * ft_sfree(ev) *
			ft_sfree(*var)));
	size = ft_strlen(buf) + ft_free(*addr);
	*addr = ft_calloc(size + 7, sizeof (char));
	ft_strlcpy(*addr, "SHLVL=", size + 7);
	ft_strlcpy(*addr + 6, buf, size + 1);
	return (ev + ft_free(buf));
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
		if (ft_execute(cmd, &ev, &var, his))
			ft_errmsg(errno);
		ft_sfree(cmd);
		prompt = ft_prompt(ev, &his);
	}
	ft_sfree(ev);
	ft_sfree(var);
	(void)ft_savhis(getenv("HOME"), HISTORY, his);
	ft_sfree(his);
	return (1);
}
