/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addhis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 21:20:05 by alfux             #+#    #+#             */
/*   Updated: 2022/08/29 23:21:50 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_addhis(char *pmt, char ***his)
{
	char	*new_his[2];
	char	**buf;

	if (!his || !pmt)
		return (EINVAL);
	if (!*his)
		*his = ft_calloc(1, sizeof (char *));
	if (!*his)
		return (errno);
	new_his[0] = ft_strdup(pmt);
	if (!new_his[0])
		return (errno);
	new_his[1] = (char *)0;
	buf = ft_strtcat(*his, new_his);
	ft_free(*his);
	*his = buf;
	add_history(pmt);
	return (0);
}
