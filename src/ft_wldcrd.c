/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wldcrd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:05:37 by alfux             #+#    #+#             */
/*   Updated: 2022/09/29 18:22:09 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_ismatch(char *candidate, t_list *tkn)
{
	char	*match;

	if (ft_strncmp(tkn->content, "*", 2))
	{
		if (ft_strncmp(candidate, tkn->content, ft_strlen(tkn->content)))
			return (0);
		candidate += ft_strlen(tkn->content);
		tkn = tkn->next;
	}
	while (tkn && !ft_strncmp(tkn->content, "*", 2))
		tkn = tkn->next;
	while (tkn)
	{
		match = ft_strnstr(candidate, tkn->content, ft_strlen(candidate));
		if (!match)
			return (0);
		candidate = match + ft_strlen(tkn->content);
		tkn = tkn->next;
		if (!tkn && candidate)
			return (0);
		while (tkn && !ft_strncmp(tkn->content, "*", 2))
			tkn = tkn->next;
	}
	return (1);
}

static int	ft_addblk(t_list **match, char *blk)
{
	t_list	*new;

	blk = ft_strdup(blk);
	if (!blk)
		return (1);
	new = ft_lstnew(blk);
	if (!new)
		return (1 + ft_free(blk));
	ft_lstadd_back(match, new);
	return (0);
}

static int	ft_match(t_list *tkn, t_list **match)
{
	struct dirent	*rd;
	DIR				*dir;

	dir = opendir(".");
	if (dir)
	{
		rd = readdir(dir + ft_errno(0));
		while (rd)
		{
			if (ft_ismatch(rd->d_name, tkn))
				if (ft_addblk(match, rd->d_name + ft_errno(0)))
					break ;
			rd = readdir(dir + ft_errno(0));
		}
		if (!errno && !closedir(dir))
			return (0);
		(void)closedir(dir);
	}
	ft_lstclear(match, (void (*)(void *))(&ft_free));
	return (1);
}

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
	t_list	*match;
	char	*str;

	if (!tkn)
		return ((t_list *)(size_t)(0 * ft_errno(EINVAL)));
	if (ft_lstsize(tkn) == 1 && ft_strncmp((char *)tkn->content, "*", 2))
		return (ft_no_wildcard(ft_strdup((char *)tkn->content)));
	match = (t_list *)0;
	if (ft_match(tkn, &match))
		return ((t_list *)0);
	if (match)
		return (match);
	str = ft_strdup(tkn->content);
	match = ft_lstnew(str);
	while (match && match->content && tkn->next)
	{
		str = match->content;
		match->content = ft_strjoin(str, tkn->next->content);
		if (match->content)
			tkn = tkn->next + (size_t)ft_free(str);
	}
	if (!ft_free(str) && match && !match->content)
		ft_lstclear(&match, (void (*)(void *))0);
	return (match);
}
