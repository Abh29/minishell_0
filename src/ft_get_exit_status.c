/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 20:28:30 by mehill            #+#    #+#             */
/*   Updated: 2022/03/05 01:47:41 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

void	ft_set_exit_status(int status)
{
	extern t_global		g_msh;

	*(g_msh.ret) = status;
}

char	*ft_get_last_exit_status(void *args)
{
	extern t_global		g_msh;
	char				*out;

	(void) args;
	out = ft_itoa(*(g_msh.ret));
	if (!out)
		out = ft_strdup("1");
	return (out);
}
