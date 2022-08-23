/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 20:05:20 by alfux             #+#    #+#             */
/*   Updated: 2022/08/23 15:43:50 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

//-----------------------------------TOOLS--------------------------------------
//Free string tabs and return 0
int		ft_sfree(char **spl);
//Free ptr and return 0
int		ft_free(void *ptr);
//Print error messages
int		ft_errmsg(int errn);
//Returns size of tab;
size_t	ft_strtlen(char **tab);
//Returns a concatenation of t1 and t2
char	**ft_strtcat(char **t1, char **t2);
//Returns a new allocated duplicate of tab
char	**ft_strtdup(char **tab);
//------------------------------------------------------------------------------

//Get new pwd (allocate memory)
char	*ft_newpwd(void);
//Returns standard input (allocate memory)
char	*ft_prompt(char **ev);
//Split the prompted command line according to (d)quotes
char	**ft_root_pmtspl(char *pmt);
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
void	ft_exit(char **av, char **ev, char **var);
//Builtin variable affectation
char	**ft_newvar(char **cmd, char **var);
//------------------------------------------------------------------------------
#endif
