/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 17:38:04 by mehill            #+#    #+#             */
/*   Updated: 2022/03/05 01:57:10 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

char	*ft_check_routines(char *out, int fd);

void	ft_routine_ctrl_d(char **line, int fd)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = NULL;
	(void)fd;
	tmp = *line;
	while (tmp2 == NULL)
		tmp2 = get_next_line(fd);
	*line = ft_strjoin(tmp, tmp2);
	free(tmp2);
	free(tmp);
}

char	*ft_routine_1(char **line, int fd)
{
	char	*tmp;
	char	*tmp2;

	tmp = *line;
	tmp[ft_strlen(tmp) - 1] = 0;
	ft_putstr_fd(">", fd);
	tmp2 = ft_get_shell_line();
	*line = ft_strjoin(tmp, tmp2);
	free(tmp2);
	free(tmp);
	return (ft_check_routines(*line, fd));
}

void	*ft_routine_2(char **line, int fd, char *msg)
{
	ft_putstr_fd(msg, fd);
	free(*line);
	*line = NULL;
	ft_set_exit_status(1);
	return (ft_strdup("\n"));
}

char	*ft_check_routines(char *out, int fd)
{
	int	err;
	int	pos;

	ft_check_cmd_line(out, &err, &pos);
	if (err == 0)
		return (out);
	if (err == 2)
		ft_routine_ctrl_d(&out, fd);
	if (err == 3)
		return (ft_routine_1(&out, fd));
	else if (err == 4)
		return (ft_routine_1(&out, fd));
	else if (err == 5)
		return (ft_routine_2(&out, fd, \
		"Error : syntax error wrong parentheses order !\n"));
	else if (err == 6 || err == 7)
		return (ft_routine_2(&out, fd, \
		"Error : unexpected syntax !\n"));
	return (out);
}

char	*ft_get_cmd_line(int fd)
{
	char	*out;

	ft_putstr_fd(SHELL_NAME, fd);
	out = ft_get_shell_line();
	return (ft_check_routines(out, fd));
}
