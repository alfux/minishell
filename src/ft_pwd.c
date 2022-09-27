/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 01:32:25 by alfux             #+#    #+#             */
/*   Updated: 2022/09/25 23:50:51 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = ft_newpwd();
	if (!pwd)
		return (1);
	ft_printf("%s\n", pwd);
	(void)ft_free(pwd);
	return (0);
}
