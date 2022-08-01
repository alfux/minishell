/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:48:07 by alfux             #+#    #+#             */
/*   Updated: 2022/08/01 02:25:02 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*ft_prompt(char *pth)
{
	char	*ret;
	size_t	size;

	size = ft_strlen(pth);
	ret = ft_calloc(size + 14, sizeof (char));
	ft_strlcpy(ret, "minishell ", size + 14);
	ft_strlcpy(ret + 10, pth, size + 4);
	ft_strlcpy(ret + size + 10, " > ", 4);
	free(pth);
	return (ret);
}

int	main(void)
{
	char	*str;
	char	*wd;

	wd = ft_prompt(getcwd((void *)0, 0));
	str = readline(wd);
	ft_printf("You teletyped: %s\n", str);
	free(str);
	free(wd);
	return (0);
}
