/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 20:05:20 by alfux             #+#    #+#             */
/*   Updated: 2022/08/31 01:31:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H
# define HISTORY ".mini_history"
# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <fcntl.h>

//-----------------------------------TOOLS--------------------------------------
//Free string tabs and return 0
int		ft_sfree(char **spl);
//Free ptr and return 0
int		ft_free(void *ptr);
//Sets errno to value and returns errno
int		ft_errno(int value);
//Print error messages
int		ft_errmsg(int errn);
//Returns size of tab;
size_t	ft_strtlen(char **tab);
//Returns a concatenation of t1 and t2
char	**ft_strtcat(char **t1, char **t2);
//Returns a new allocated duplicate of tab
char	**ft_strtdup(char **tab);
//Returns adress of pointer on variable str in tab, returns 0 if not found
char	**ft_isvarin(char *str, char **tab);
//Delete addr from tab
int		ft_strtdelone(char **addr, char ***tab);
//------------------------------------------------------------------------------

//Get new pwd (allocate memory)
char	*ft_newpwd(void);
//Returns standard input (allocate memory)
char	*ft_prompt(char **ev, char ***his);
//Split the prompted command line according to (d)quotes
char	**ft_cmdspl(char *pmt);
//Parse	the split command line to remove (d)quotes and replaces variables ($)
char	**ft_root_parse(char **cmd, char **ev, char **var);
//Execute the parsed command line
void	ft_execute(char **cmd, char ***ev, char ***var, char **his);
//Search the builtins to match command line (récup ft_isntvar)
int		ft_isbuiltin(char **cmd, char ***ev, char ***var, char **his);
//Returns non zero if cmd has another command than variable affectation
int		ft_isntvar(char **cmd);
//Add the last typed command line to history and his tab
int		ft_addhis(char *pmt, char ***his);
//Saves history in a file
int		ft_savhis(char *fname, char **his);
//Adds history stored in fname file
int		ft_gethis(char *fname);

//---------------------------------BUILTINS-------------------------------------
//Builtin echo with -n option
int		ft_echo(char **av);
//Buildin cd
char	**ft_cd(char **av, char **ev);
//Builtin pwd without option
int		ft_pwd(void);
//Builtin env without option or argument
int		ft_env(char **ev);
//Builtin exit without option
void	ft_exit(char **av, char **ev, char **var, char **his);
//Builtin variable affectation
char	**ft_setvar(char **av, char **ev, char **var);
//Builtin export without option
int		ft_export(char **av, char ***ev, char ***var);//Rework for lists
//Builtin unset without option
int		ft_unset(char **av, char ***ev, char ***var);
//------------------------------------------------------------------------------
#endif
