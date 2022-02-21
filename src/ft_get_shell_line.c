/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_shell_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 21:43:55 by mehill            #+#    #+#             */
/*   Updated: 2022/02/22 01:19:07 by mehill           ###   ########.fr       */
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
	while (i < 4095)
	{
		c = ft_getchar(STDIN_FILENO);
	//	printf("\n%d  %c  %d  >\n", c, c, i);
		if ((c == 0 || c == 4) && i == 0)
			return (ft_strdup("exit\n"));
		if (c == 0 || c == 4)
			continue ;
		if (c == 21)
			while (i > 0 && write(STDIN_FILENO, "\b \b", 3))
				i--;
		if (c == 127 && i > 0 && write(STDIN_FILENO, "\b \b", 3))
			buff[--i] = 0;
		else if ((ft_isprint(c) || ft_isspace(c)))
			buff[i++] = c;
		if (c == EOF || c == 10)
			break ;
	}
	buff[i] = 0;
	return (ft_strdup(buff));
}
