/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 20:05:20 by alfux             #+#    #+#             */
/*   Updated: 2022/08/08 22:41:11 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <readline/readline.h>
# include <errno.h>

//Returns standard input, needs free
char	*ft_prompt(char **ev);
//Buildin cd
int		ft_cd(char *path, char **ev);
//Duplicate environnement, needs free
char	**ft_envdup(char **ev);
//Free string tabs
int		ft_sfree(char **spl);
#endif
