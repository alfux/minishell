/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_macro_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 20:36:36 by alfux             #+#    #+#             */
/*   Updated: 2022/09/23 16:08:52 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_to_next_logical_operator(char **av, int start)
{
	while (*(av + start) && ft_strncmp(*(av + start), "&&", 3)
		&& ft_strncmp(*(av + start), "||", 3))
	{
		if (!ft_strncmp(*(av + start), "(", 2))
			start = ft_skppar(av, start);
		else
			start++;
	}
	return (start);
}

int	ft_macro_exec(char **av, char ***ev, char ***var, char **his)
{
	char	**buf;
	int		exit_status;
	int		size;
	int		i;

	i = 0;
	size = ft_to_next_logical_operator(av, i);
	if (!*(av + size))
		return (ft_execute(av, ev, var, his));
	while (*(av + i))
	{
		buf = ft_substrt(av, i, size - i);
		if (!buf)
			return (ft_errmsg(errno));
		exit_status = ft_execute(buf, ev, var, his);
		(void)ft_sfree(buf);
		if (ft_exit_toggle(STATE) || !*(av + size)
			|| (!ft_strncmp(*(av + size), "&&", 3) && exit_status)
			|| (!ft_strncmp(*(av + size), "||", 3) && !exit_status))
			return (exit_status);
		i = size + 1;
		size = ft_to_next_logical_operator(av, i);
	}
	return (exit_status);
}
