/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isstrin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:04:55 by alfux             #+#    #+#             */
/*   Updated: 2022/08/24 15:41:57 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**ft_isstrin(char *str, char **tab)
{
	size_t	size;
	int		i;

	if (!tab || !*tab)
		return ((char **)0);
	size = 0;
	while (*(str + size) && *(str + size) != '=')
		size++;
	i = 0;
	while (*(tab + i))
	{
		if (!ft_strncmp(str, *(tab + i), size + 1))
			return (tab + i);
		i++;
	}
	return ((char **)0);
}
