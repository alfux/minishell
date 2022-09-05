/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:48:07 by alfux             #+#    #+#             */
/*   Updated: 2022/09/06 00:47:25 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	**ft_setenv(char **ev, char ***var, char ***his)
{
	size_t	size;
	char	**addr;
	char	*buf;

	*var = (char **)0;
	*his = ft_calloc(1, sizeof (char *));
	if (!*his)
		return ((char **)(size_t)(0 * ft_errmsg(errno)));
	if (ft_gethis(getenv("HOME"), HISTORY))
		ft_errmsg(-8 + (0 * ft_errmsg(errno)));
	ev = ft_strtdup(ev);
	if (!ev)
		return ((char **)(size_t)(ft_sfree(*his) * ft_errmsg(errno)));
	addr = ft_isvarin("SHLVL=", ev);
	buf = ft_itoa(ft_atoi(*addr + 6) + 1);
	if (!buf)
		return ((char **)(size_t)(ft_sfree(*his) * ft_sfree(ev) *
			ft_errmsg(errno)));
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
	int		i = 0;
	pid_t	*pid;

	ev = ft_setenv(ev, &var, &his);
	if (!ev || !ac || !av)
		return (1);
	prompt = ft_prompt(ev, &his);
	while (prompt)
	{
		cmd = ft_cmdspl(prompt);
		ft_bzero(&pid, sizeof (pid_t *));
		ft_free(prompt);
		if (cmd)
			cmd = ft_pipmkr(cmd, &pid);
		if (cmd)
		{
			cmd = ft_root_parse(cmd, ev, var);
			if (cmd)
				ft_execute(cmd, &ev, &var, his);
			if (pid)
				ft_exit(cmd, ev, var, (char **)(size_t)ft_sfree(his) + ft_free(pid));

		}
		else if (cmd == (char **)-1)
			ft_errmsg(errno);
		else
			while (*(pid + i) != (pid_t)-1)
				waitpid(*(pid + i++), (int *)0, 0);
		i = 0;
		ft_sfree(cmd + ft_free(pid));
		prompt = ft_prompt(ev, &his);
	}
	ft_sfree(ev);
	ft_sfree(var);
	(void)ft_savhis(getenv("HOME"), HISTORY, his);
	ft_sfree(his);
	return (1);
}
