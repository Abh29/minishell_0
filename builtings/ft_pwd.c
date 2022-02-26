/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:05:45 by ddelena           #+#    #+#             */
/*   Updated: 2022/02/26 03:15:01 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

void	ft_pwd(void)
{
	char	*buf;

	buf = ft_calloc(4096, 1);
	if (getcwd(buf, 4096))
	{
		ft_putstr_fd(buf, 1);
		free(buf);
		write(1, "\n", 1);
		exit(0);
	}
	print_error();
	free(buf);
	exit(1);
}
