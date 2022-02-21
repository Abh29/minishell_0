/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_shell_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 21:43:55 by mehill            #+#    #+#             */
/*   Updated: 2022/02/21 23:25:40 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

int	ft_getchar(int fd)
{
	char	out[2];

	if (fd < 0)
		return (-1);
	out[0] = 0;
	out[1] = 0;
	if (read (fd, out, 1) < 0)
		return (-1);
	return (*out);
}

char	*ft_get_shell_line(void)
{
	char	buff[4097];
	int		i;
	int		c;

	i = 0;
	ft_bzero(buff, 4097);
	buff[4095] = '\n';
	while (i < 4095)
	{
		c = ft_getchar(STDIN_FILENO);
		if (c == 4 && i == 0)
			return (ft_strdup("exit"));
		if (c == EOF || c == 12 || c == '\n')
			break ;
		buff[i++] = c;
	}
	buff[i] = 0;
	return (ft_strdup(buff));
}
