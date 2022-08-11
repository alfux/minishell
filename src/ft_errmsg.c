/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errmsg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:40:11 by alfux             #+#    #+#             */
/*   Updated: 2022/08/11 15:03:49 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_errmsg(int errn)
{
	if (errn == EACCES)
		ft_putstr_fd("Error: Permission denied\n", 2);
	else if (errn == EFAULT)
		ft_putstr_fd("Error: Path is outside of allocated address space\n", 2);
	else if (errn == EIO)
		ft_putstr_fd(
			"Error: I/O error occured while read/write file system\n", 2);
	else if (errn == ELOOP)
		ft_putstr_fd(
			"Error: Too many symbolic links, this may be a looping\n", 2);
	else if (errn == ENAMETOOLONG)
		ft_putstr_fd("Error: Path/name is too long", 2);
	else if (errn == ENOENT)
		ft_putstr_fd("Error: Component of pathname does not exist\n", 2);
	else if (errn == ENOTDIR)
		ft_putstr_fd("Error: Not a directory\n", 2);
	else if (errn == ENOMEM)
		ft_putstr_fd("Error: Insufficient memory available\n", 2);
	else if (errn == EINVAL)
		ft_putstr_fd("Error: Invalid argument value\n", 2);
	else if (errn == ERANGE)
		ft_putstr_fd("Error: Argument(s) out of range\n", 2);
	else
		ft_putstr_fd("Error: Unknown\n", 2);
	return (errn);
}
