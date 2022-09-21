/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extsta.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:48:07 by alfux             #+#    #+#             */
/*   Updated: 2022/09/16 15:54:30 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_decode_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	else
		return (status);
}

char	*ft_extsta(int exit_status, char *prev_status)
{
	size_t	size;
	char	*new;
	char	*buf;

	buf = ft_itoa(ft_decode_status(exit_status));
	if (!buf)
		return (prev_status + (0 * ft_errmsg(errno)));
	size = ft_strlen(buf);
	new = ft_calloc(size + 3, sizeof (char));
	if (!new)
		return (prev_status + (ft_free(buf) * ft_errmsg(errno)));
	ft_strlcpy(new, "?=", size + 3);
	ft_strlcpy(new + 2, buf, size + 1);
	return (new + ft_free(prev_status) + ft_free(buf));
}
