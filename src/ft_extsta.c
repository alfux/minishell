/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extsta.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:48:07 by alfux             #+#    #+#             */
/*   Updated: 2022/09/07 03:24:24 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*ft_extsta(int exit_status, char *prev_status)
{
	size_t	size;
	char	*new;
	char	*buf;

	buf = ft_itoa(exit_status);
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
