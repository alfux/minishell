/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:05:37 by alfux             #+#    #+#             */
/*   Updated: 2022/10/05 16:18:59 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_addblk(t_list **match, char *blk, char *dir)
{
	t_list	*new;

	if (dir)
	{
		if (*(dir + ft_strlen(dir) - 1) != '/')
			dir = ft_strjoin(dir, "/");
		else 
			dir = ft_strdup(dir);
		if (!dir)
			return (1);
		blk = ft_strjoin(dir, blk);
		(void)ft_free(dir);
	}
	else
		blk = ft_strdup(blk);
	if (!blk)
		return (1);
	new = ft_lstnew(blk);
	if (!new)
		return (1 + ft_free(blk));
	ft_lstadd_back(match, new);
	return (0);
}

static int	ft_subsch(char *subdir, char *schdir, t_list *tkn, t_list **match)
{
	int	tmp;

	if (schdir)
	{
		if (*(schdir + ft_strlen(schdir) - 1) != '/')
			subdir = ft_strjoin("/", subdir);
		else
			subdir = ft_strdup(subdir);
		if (!subdir)
			return (-1);
		schdir = ft_strjoin(schdir, subdir);
		(void)ft_free(subdir);
	}
	else
		schdir = ft_strdup(subdir);
	tmp = ft_isdir(schdir);
	if (tmp == -1)
		return (-1 + ft_free(schdir));
	if (!tmp)
		return (0 + ft_free(schdir));
	if (!tkn)
		return (1 + ft_free(schdir));
	if (ft_search(schdir, tkn, match))
		return (-1 + ft_free(schdir));
	return (0 + ft_free(schdir));
}

static int	ft_ismatch(char *candidate, char *schdir, t_list *tkn, t_list **mth)
{
	char	*match;
	char	*start;

	start = candidate;
	if (ft_strncmp(tkn->content, "*", 2))
		if (ft_strncmp(candidate, tkn->content, ft_strlen(tkn->content) + 1))
			return (0);
	if (ft_strncmp(tkn->content, "*", 2))
		candidate += ft_strlen(tkn->content);
	tkn = tkn->next;
	tkn = ft_skptkn(tkn, "*");
	while (tkn)
	{
		if (!ft_strncmp(tkn->content, "/", 2))
			return (ft_subsch(start, schdir, ft_skptkn(tkn, "/"), mth));
		match = ft_strnstr(candidate, tkn->content, ft_strlen(candidate));
		if (!match)
			return (0);
		candidate = match + ft_strlen(tkn->content);
		tkn = tkn->next;
		if ((!tkn || !ft_strncmp(tkn->content, "/", 2)) && *candidate)
			return (0);
		tkn = ft_skptkn(tkn, "*");
	}
	return (1);
}

static struct dirent	*ft_readdir(DIR *dir, t_list *tkn)
{
	struct dirent	*rd;

	(void)ft_errno(0);
	rd = readdir(dir);
	if (!rd)
		return ((struct dirent *)0);
	if (tkn && !ft_strncmp((char *)tkn->content, "*", 2))
		if (!ft_strncmp(rd->d_name, ".", 1))
			return (ft_readdir(dir, tkn));
	return (rd);
}

int	ft_search(char *schdir, t_list *tkn, t_list **match)
{
	struct dirent	*rd;
	DIR				*dir;
	int				re;

	if (!ft_strncmp(tkn->content, "/", 2))
		return (0);
	if (!schdir)
		dir = opendir(".");
	else
		dir = opendir(schdir);
	if (dir)
	{
		rd = ft_readdir(dir, tkn);
		while (rd)
		{
			re = ft_ismatch(rd->d_name, schdir, tkn, match);
			if (re == -1 || (re && ft_addblk(match, rd->d_name, schdir)))
				break ;
			rd = ft_readdir(dir, tkn);
		}
		if ((!errno || (0 * closedir(dir))) && !closedir(dir))
			return (0);
	}
	ft_lstclear(match, (void (*)(void *))(&ft_free));
	return (1);
}
