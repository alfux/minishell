/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigmsg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:23:46 by alfux             #+#    #+#             */
/*   Updated: 2022/09/15 20:31:44 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_sigmsg(int exit_status)
{
	if (WIFSIGNALED(exit_status) && WTERMSIG(exit_status) == SIGINT)
		return ((void)write(1, "\n", 1));
	else if (WIFSIGNALED(exit_status))
		return ((void)ft_printf("Quit: %i\n", WTERMSIG(exit_status)));
}
