/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 23:21:20 by mehill            #+#    #+#             */
/*   Updated: 2021/11/12 20:10:23 by mehill           ###   ########.fr       */
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

void	ft_print_io_red(t_io_red *red, int fd)
{
	ft_putstr_fd("in : ", fd);
	ft_putnbr_fd(red->fdin, fd);
	ft_putstr_fd("\nout : ", fd);
	ft_putnbr_fd(red->fdout, fd);
	ft_putstr_fd("\nlimiter : ", fd);
	ft_putstr_fd(red->limiter, fd);
	ft_putstr_fd("\nappend : ", fd);
	ft_putnbr_fd(red->append, fd);
	ft_putstr_fd("\n", fd);
}

void	ft_print_cmd(t_cmd *cmd, int fd)
{
	ft_putstr_fd("cmd_name : ", fd);
	ft_putstr_fd(cmd->cmd_name, fd);
	ft_putstr_fd("\nargs : \n", fd);
	ft_print_splt(cmd->args, fd);
	ft_putstr_fd("io redirections : \n", fd);
	ft_print_io_red(cmd->red, fd);
	ft_putstr_fd("\n", fd);
	ft_putstr_fd("pipes : ", fd);
	ft_putnbr_fd(ft_dlstsize(cmd->pipe), fd);
	ft_putstr_fd("\n", fd);
}

void	ft_print_cmd_list(t_dlist *cmds, int fd)
{
	ft_putstr_fd("list size : ", fd);
	ft_putnbr_fd(ft_dlstsize(cmds), fd);
	ft_putstr_fd("\n", fd);
	ft_putstr_fd("\n****************\n", fd);
	while (cmds)
	{
		ft_print_cmd(cmds->content, fd);
		ft_putstr_fd("\n****************\n", fd);
		cmds = cmds->next;
	}
}
