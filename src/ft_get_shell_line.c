/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_shell_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 21:43:55 by mehill            #+#    #+#             */
/*   Updated: 2022/02/23 14:33:39 by mehill           ###   ########.fr       */
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

void	ft_reset_input_buff(void)
{
	extern t_global	g_msh;

	while (g_msh.buff_idx > 0 && write(STDIN_FILENO, "\b \b", 3))
		g_msh.buff_idx--;
	ft_bzero(g_msh.buff, 4097);
}

char	*ft_get_shell_line(void)
{
	extern t_global	g_msh;
	int				c;

	g_msh.buff_idx = 0;
	ft_bzero(g_msh.buff, 4097);
	while (g_msh.buff_idx < 4095)
	{
		c = ft_getchar(STDIN_FILENO);
		printf("\n%d  %c  %d  >\n", c, c, g_msh.buff_idx);
		if ((c == 0 || c == 4) && g_msh.buff_idx == 0)
			return (ft_strdup("exit\n"));
		if (c == 0 || c == 4)
			continue ;
		if (c == 21)
			ft_reset_input_buff();
		if (c == 127 && g_msh.buff_idx > 0 && write(STDIN_FILENO, "\b \b", 3))
			g_msh.buff[--g_msh.buff_idx] = 0;
		else if ((ft_isprint(c) || ft_isspace(c)))
			g_msh.buff[g_msh.buff_idx++] = c;
		if (c == EOF || c == 10)
			break ;
	}
	g_msh.buff[g_msh.buff_idx] = 0;
	return (ft_strdup(g_msh.buff));
}
