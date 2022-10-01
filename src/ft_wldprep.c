/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wldprep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 01:14:36 by alfux             #+#    #+#             */
/*   Updated: 2022/10/01 13:41:14 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_addblk(t_list **tkn, char *blk)
{
	t_list	*new;

	if (blk)
	{
		new = ft_lstnew(blk);
		if (new)
		{
			ft_lstadd_back(tkn, new);
			return (0);
		}
		(void)ft_free(blk);
	}
	ft_lstclear(tkn, (void (*)(void *))(&ft_free));
	return (1);
}

static t_list	*ft_wldtkn(char *ptrn)
{
	t_list	*tkn;
	size_t	i;

	tkn = (t_list *)0;
	if (!*ptrn)
		(void)ft_addblk(&tkn, ft_strdup(ptrn));
	while (*ptrn)
	{
		i = 0;
		while (*(ptrn + i) && *(ptrn + i) != '*' && *(ptrn + i) != '/')
		{
			if (*(ptrn + i) == '\'' || *(ptrn + i) == '\"')
				i = ft_skpqts(ptrn, i);
			else
				i++;
		}
		if (i && ft_addblk(&tkn, ft_substr(ptrn, 0, i)))
			return ((t_list *)0);
		if ((*(ptrn + i) == '*' && ft_addblk(&tkn, ft_strdup("*")))
			|| (*(ptrn + i) == '/' && ft_addblk(&tkn, ft_strdup("/"))))
			return ((t_list *)0);
		ptrn += i + !!*(ptrn + i);
	}
	return (tkn);
}

static int	ft_lstparse(t_list **tkn, char **ev, char **var)
{
	t_list	*buf;
	char	*tmp[2];

	buf = *tkn;
	*(tmp + 1) = (char *)0;
	while (buf)
	{
		*tmp = buf->content;
		if (ft_root_parse(tmp, ev, var))
		{
			ft_lstclear(tkn, (void (*)(void *))(&ft_free));
			return (1);
		}
		buf->content = *tmp;
		buf = buf->next;
	}
	return (0);
}

static t_list	*ft_rem_mty_tkn(t_list *tkn)
{
	t_list	*nav;
	t_list	*buf;

	nav = tkn;
	while (nav && !*(char *)nav->content)
	{
		tkn = nav->next;
		ft_lstdelone(nav, (void (*)(void *))(&ft_free));
		nav = tkn;
	}
	while (nav->next)
	{
		if (!*(char *)nav->next->content)
		{
			buf = nav->next;
			nav->next = nav->next->next;
			ft_lstdelone(buf, (void (*)(void *))(&ft_free));
		}
		else
			nav = nav->next;
	}
	return (tkn);
}

t_list	*ft_wldprep(char *pattern, char **ev, char **var)
{
	t_list	*wldtkn;
	size_t	i;
	int		go;

	if (!pattern)
		return ((t_list *)(size_t)(0 * ft_errno(EINVAL)));
	i = 0;
	go = 0;
	wldtkn = (t_list *)0;
	while (*(pattern + i) && !go)
	{
		if (*(pattern + i) == '\"' || *(pattern + i) == '\'')
			i = ft_skpqts(pattern, i);
		else if (*(pattern + i) == '*')
			go = 1 + (0 * i++);
		else
			i++;
	}
	if (go)
		wldtkn = ft_wldtkn(pattern);
	else if (ft_addblk(&wldtkn, ft_strdup(pattern)))
		return ((t_list *)0);
	if (!wldtkn || ft_lstparse(&wldtkn, ev, var))
		return ((t_list *)0);
	return (ft_rem_mty_tkn(wldtkn));
}
