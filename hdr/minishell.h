/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 20:05:20 by alfux             #+#    #+#             */
/*   Updated: 2022/08/21 00:54:20 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

//Free string tabs and return 0
int		ft_sfree(char **spl);
//Free ptr and return 0
int		ft_free(void *ptr);
//Print error messages
int		ft_errmsg(int errn);
//Duplicate environnement (allocate memory)
char	**ft_envdup(char **ev);
//Get new pwd (allocate memory)
char	*ft_newpwd(void);
//Returns standard input (allocate memory)
char	*ft_prompt(char **ev);
//Split the prompted command line according to (d)quotes
char	**ft_root_cmdspl(char *cmd);
//Parse	the split command line to removes (d)quotes and replaces variables ($)
char	**ft_root_parse(char **cmd, char **ev, char **var);
//Execute the parsed command line
void	ft_execute(char **cmd, char ***ev, char ***var);
//Search the builtins to match command line
int		ft_isbuiltin(char **cmd, char ***ev, char ***var);

//---------------------------------BUILTINS-------------------------------------
//Builtin echo
int		ft_echo(char **av);
//Buildin cd
int		ft_cd(char **av, char **ev);
//Builtin pwd
int		ft_pwd(void);
//Builtin env
int		ft_env(char **ev);
//Builtin exit
void	ft_exit(char **av, char **ev);
//Builtin variable affectation
char	**ft_newvar(char **cmd, char **var);
//------------------------------------------------------------------------------
#endif
