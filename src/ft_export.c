/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:56:46 by alfux             #+#    #+#             */
/*   Updated: 2022/08/26 10:37:48 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_alphaprint(char **ev, char const *prv)
{
	char	*print;
	int		i;

	i = 0;
	print = (char *)0;
	while (*(ev + i))
	{
		if ((!*prv || ft_strncmp(*(ev + i), prv, ft_maxof(ft_strlen(*(ev + i)),
			ft_strlen(prv))) < 0) && (!print || ft_strncmp(*(ev + i), print,
			ft_maxof(ft_strlen(print), ft_strlen(*(ev + i)))) > 0))
			print = *(ev + i);
		i++;
	}
	if (!print)
		return (0);
	ft_alphaprint(ev, print);
	ft_printf("declare -x %c", *print);
	while (*(++print) && *(print - 1) != '=')
		ft_putchar_fd(*print, 1);
	ft_putchar_fd('\"', 1);
	ft_printf("%s\"\n", print);
	return (0);
}

static int	ft_iseq(char *str)
{
	while (*str)
		if (*(str++) == '=')
			return (1);
	return (0);
}

int	ft_export(char **av, char ***ev, char ***var)
{
	(void)var;
	ft_iseq(**ev);
	if (!*(av + 1))
		return (ft_alphaprint(*ev, "\0"));
	return (0);
}
