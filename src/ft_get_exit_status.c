/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 20:28:30 by mehill            #+#    #+#             */
/*   Updated: 2021/12/05 20:28:51 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

char	*ft_get_last_exit_status(void *args)
{
	extern	t_global	g_msh;
	char				*out;
	(void) args;
	out = ft_itoa(*(g_msh.ret));
	if (!out)
		out = ft_strdup("1");
	return (out);
}
