/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_waitall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:38:57 by alfux             #+#    #+#             */
/*   Updated: 2022/09/16 01:14:53 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

pid_t	ft_waitall(pid_t *pid, int *exit_status, int opt)
{
	pid_t	ret;
	int		i;

	ret = 0;
	i = 0;
	while (*(pid + i))
		ret = waitpid(0 * i++, exit_status, opt);
	return (ret);
}
