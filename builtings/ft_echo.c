/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:13:56 by ddelena           #+#    #+#             */
/*   Updated: 2022/02/26 03:06:05 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

int	ft_echo(t_cmd *cmd)
{
	int	flag;
	int	i;

	flag = 0;
	i = 1;
	if (cmd->args)
	{
		while (cmd->args[i] && ft_strncmp("-n", cmd->args[i], 2) == 0)
		{
			flag = 1;
			i++;
		}
		while (cmd->args[i])
		{
			ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
			if (cmd->args[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (!flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	exit(0);
}
