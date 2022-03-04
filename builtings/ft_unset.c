/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:14:10 by ddelena           #+#    #+#             */
/*   Updated: 2022/03/04 02:32:24 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

void	ft_unset(t_cmd *cmd)
{
	int	i;

	if (cmd == NULL)
		ft_exit("Error : calling ft_unset with NULL arg !\n", 1);
	ft_get_envp();
	i = 1;
	while (cmd->args[i])
	{
		ft_dellenv(cmd->args[i++]);
		ft_set_envp();
	}
	exit(0);
}
