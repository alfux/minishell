/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:16:44 by alfux             #+#    #+#             */
/*   Updated: 2022/10/01 18:46:47 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	**ft_ltot(t_list *lst)
{
	char	**new;
	int		i;

	new = ft_calloc(ft_lstsize(lst) + 1, sizeof (char *));
	if (!new)
		return ((char **)0);
	i = 0;
	while (lst)
	{
		*(new + i++) = lst->content;
		lst = lst->next;
	}
	return (new);
}

static int	ft_parse_first(char *first, char **ev, char **var, t_list **lst)
{
	t_list	*match;
	t_list	*tkn;
	char	*sdup;

	sdup = (char *)0;
	if (!ft_strncmp(first, "/", 1) || !ft_strncmp(first, "./", 2)
		|| !ft_strncmp(first, "../", 3))
	{
		tkn = ft_wldprep(first, ev, var);
		if (!tkn)
			return (1);
		match = ft_match(tkn);
		ft_lstclear(&tkn, (void (*)(void *))(&ft_free));
	}
	else
	{
		sdup = ft_strdup(first);
		if (!sdup)
			return (1);
		match = ft_lstnew(sdup);
	}
	if (!match)
		return (1 + ft_free(sdup));
	*lst = match;
	return (0);
}

static int	ft_parse_next(char *next, char **ev, char **var, t_list **lst)
{
	t_list	*match;
	t_list	*tkn;

	tkn = ft_wldprep(next, ev, var);
	if (!tkn)
	{
		ft_lstclear(lst, (void (*)(void *))(&ft_free));
		return (1);
	}
	match = ft_match(tkn);
	ft_lstclear(&tkn, (void (*)(void *))(&ft_free));
	if (!match)
	{
		ft_lstclear(lst, (void (*)(void *))(&ft_free));
		return (1);
	}
	ft_lstadd_back(lst, match);
	return (0);
}

int	ft_parse(char ***av, char **ev, char **var)
{
	t_list	*match;
	char	**new;
	int		i;

	if (!**av)
	{
		new = ft_calloc(1, sizeof (char *));
		if (!new)
			return (1);
		*av = new;
		return (0);
	}
	if (ft_parse_first(**av, ev, var, &match))
		return (1);
	i = 1;
	while (*(*av + i))
		if (ft_parse_next(*(*av + i++), ev, var, &match))
			return (1);
	new = ft_ltot(match);
	ft_lstclear(&match, (void (*)(void *))0);
	if (!new)
		return (1);
	*av = new;
	return (0);
}
