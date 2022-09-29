/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wldcrd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:05:37 by alfux             #+#    #+#             */
/*   Updated: 2022/09/28 18:55:21 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static t_list	*ft_no_wildcard(char *str)
{
	t_list	*new;

	if (!str)
		return ((t_list *)0);
	new = ft_lstnew(str);
	if (!new)
		return ((t_list *)(size_t)ft_free(str));
	return (new);
}

t_list	*ft_wldcrd(t_list *tkn)
{
	if (!tkn)
		return ((t_list *)(size_t)(0 * ft_errno(EINVAL)));
	if (ft_lstsize(tkn) == 1 && ft_strncmp((char *)tkn->content, "*", 2))
		return (ft_no_wildcard(ft_strdup((char *)tkn->content)));
	while (tkn)
	{
		
	}
}
