/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 23:21:20 by mehill            #+#    #+#             */
/*   Updated: 2021/11/03 21:20:35 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

void	ft_print_splt(char	**spt, int fd)
{
	while (*spt)
	{
		ft_putstr_fd(*spt, fd);
		ft_putstr_fd("\n", fd);
		spt++;
	}
}

void	ft_print_io_red(t_io_red *red)
{
	ft_putstr_fd("in : ", 1);
	ft_putnbr_fd(red->fdin, 1);
	ft_putstr_fd("\nout : ", 1);
	ft_putnbr_fd(red->fdout, 1);
	ft_putstr_fd("\nlimiter : ", 1);
	ft_putstr_fd(red->limiter, 1);
	ft_putstr_fd("\nappend : ", 1);
	ft_putnbr_fd(red->append, 1);
	ft_putstr_fd("\n", 1);
}
