/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 20:05:20 by alfux             #+#    #+#             */
/*   Updated: 2022/08/18 14:07:33 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

//Get new pwd (allocate memory)
char	*ft_newpwd(void);
//Returns standard input (allocate memory)
char	*ft_prompt(char **ev);
//Buildin cd
int		ft_cd(char **path, char **ev);
//Duplicate environnement (allocate memory)
char	**ft_envdup(char **ev);
//Free string tabs and return 0
int		ft_sfree(char **spl);
//Free ptr and return 0
int		ft_free(void *ptr);
//Show environnement
int		ft_env(char **ev);
//Print error messages
int		ft_errmsg(int errn);
//Echo buildin function, prints operands
int		ft_echo(char **av);
//Split the prompted command line according to (d)quotes
char	**ft_root_cmdspl(char *cmd);
//Parse	the split command line to removes (d)quotes and replaces variables ($)
char	**ft_root_parse(char **cmd, char **ev);
#endif
