/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:40:11 by alfux             #+#    #+#             */
/*   Updated: 2022/08/08 22:53:04 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_errmsg(int errn)
{
	if (errn == EACCES)
		ft_printf("Error: Permission denied\n");
	else if (errn == EFAULT)
		ft_printf("Error: Path is outside of allocated address space\n");
	else if (errn == EIO)
		ft_printf("Error: I/O error occured while read/write file system\n");
	else if (errn == ELOOP)
		ft_printf("Error: Too many symbolic links, this may be a looping\n");
	else if (errn == ENAMETOOLONG)
		ft_printf("Error: Path/name is too long: NAME_MAX: %i PATH_MAX:%i\n",
			NAME_MAX, PATH_MAX);
	else if (errn == ENOENT)
		ft_printf("Error: Directory does not exist\n");
	else if (errn == ENOTDIR)
		ft_printf("Error: Not a directory\n");
	return (errn);
}

int	ft_cd(char *path, char **ev)
{
	(void)ev;
	if (chdir(path))
		return (ft_errmsg(errno));
	return (0);
}
