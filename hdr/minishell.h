/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 20:05:20 by alfux             #+#    #+#             */
/*   Updated: 2022/09/07 02:57:30 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H
# define HISTORY ".minishell_history"
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
//Copies src into dst, but with strings tabs (uses strdups)
int		ft_strtlcpy(char **dst, char **src, int dstsize);
//Return a copy of a sub-stringtab
char	**ft_substrt(char **strt, int start, int len);
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
int		ft_execute(char **av, char ***ev, char ***var, char **his);
//Search the builtins to match command line (récup ft_isntvar)
int		ft_isbuiltin(char **cmd, char ***ev, char ***var, char **his);
//Initialize var to contain at least "$?" for last process exit status
char	**ft_init_var(void);
//Returns the environnement variables and sets var and his
char	**ft_setenv(char **ev, char ***var, char ***his);
//Returns non zero if cmd has another command than variable affectation
int		ft_isntvar(char **cmd);
//Add the last typed command line to history and his tab
int		ft_addhis(char *pmt, char ***his);
//Saves history in a file
int		ft_savhis(char *path, char *fname, char **his);
//Adds history stored in fname file
int		ft_gethis(char *path, char *fname);
//Tries to start external binaries, returns non-zero if an error occurs
pid_t	ft_isextern(char **av, char **ev, pid_t (*e)(char *, char **, char **));
//Forks a child to hold the call to execve, parent process gets pid
pid_t	ft_newpro(char *path, char **av, char **ev);
//Make forks linked by pipes, returns null in parent and each cmd in childs
char	**ft_pipmkr(char **av, pid_t **pid);//RETHINK ARCHITECTURE OF THIS
//Returns a string for new exit status $="" and frees previous one
char	*ft_extsta(int exit_status, char *prev_status);

//---------------------------------BUILTINS-------------------------------------
//Builtin echo with -n option
int		ft_echo(char **av);
//Buildin cd
int		ft_cd(char **av, char ***ev);
//Builtin pwd without option
int		ft_pwd(void);
//Builtin env without option or argument
int		ft_env(char **ev);
//Builtin exit without option
void	ft_exit(char **av, char **ev, char **var, char **his);
//Builtin variable affectation
int		ft_setvar(char **av, char **ev, char ***var);
//Builtin export without option
int		ft_export(char **av, char ***ev, char ***var);//Rework for lists
//Builtin unset without option
int		ft_unset(char **av, char ***ev, char ***var);
//------------------------------------------------------------------------------
#endif
