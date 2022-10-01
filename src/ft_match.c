/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:05:37 by alfux             #+#    #+#             */
/*   Updated: 2022/10/01 05:31:48 by alfux            ###   ########.fr       */
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

static int	ft_dir_or_not(t_list *tkn, t_list **match)
{
	t_list	*nav;

	if (!ft_strncmp((char *)tkn->content, "/", 2))
	{
		nav = ft_skptkn(tkn->next, "/");
		if (nav)
			return (ft_search("/", nav, match));
		return (ft_search("/", tkn, match));
	}
	if (!ft_strncmp((char *)tkn->content, "..", 3)
		&& tkn->next && !ft_strncmp((char *)tkn->next->content, "/", 2))
	{
		nav = ft_skptkn(tkn->next, "/");
		if (nav)
			return (ft_search("..", nav, match));
		return (ft_search("..", tkn, match));
	}
	if (!ft_strncmp((char *)tkn->content, ".", 2)
		&& tkn->next && !ft_strncmp((char *)tkn->next->content, "/", 2))
	{
		nav = ft_skptkn(tkn->next, "/");
		if (nav)
			return (ft_search(".", nav, match));
	}
	return (ft_search(".", tkn, match));
}

t_list	*ft_match(t_list *tkn)
{
	t_list	*match;
	char	*str;

	if (!tkn)
		return ((t_list *)(size_t)(0 * ft_errno(EINVAL)));
	if (ft_lstsize(tkn) == 1 && ft_strncmp((char *)tkn->content, "*", 2))
		return (ft_no_wildcard(ft_strdup((char *)tkn->content)));
	match = (t_list *)0;
	if (ft_dir_or_not(tkn, &match))
		return ((t_list *)0);
	if (match)
		return (match);
	str = ft_strdup(tkn->content);
	match = ft_lstnew(str);
	while (match && match->content && tkn->next)
	{
		str = match->content;
		match->content = ft_strjoin(str, tkn->next->content);
		(void)ft_free(str);
		tkn = tkn->next;
	}
	if (match && !match->content)
		ft_lstclear(&match, (void (*)(void *))0);
	return (match);
}
