/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:14:01 by ddelena           #+#    #+#             */
/*   Updated: 2022/02/26 01:46:47 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

int	ft_env(void)
{
	extern t_global	g_msh;
	int				i;

	i = 0;
	ft_get_envp();
	while (g_msh.envp[i])
	{
		ft_putstr_fd(g_msh.envp[i++], 1);
		write (1, "\n", 1);
	}
	return (0);
}
