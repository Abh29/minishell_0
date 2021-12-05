/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 20:28:38 by mehill            #+#    #+#             */
/*   Updated: 2021/12/05 20:34:08 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

char	*ft_next_pipe(char *str)
{
	int	q;

	q = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			if (q == 0)
				q = *str;
			else if (q == *str)
				q = 0;
		}
		else if (q == 0 && *str == '|' && *(str - 1) != '\\')
			return (str);
		str++;
	}
	return (NULL);
}

int	ft_pipes_count(char *line)
{
	int	out;

	out = 0;
	if (line)
		line = ft_next_pipe(line);
	while (line && out++ > -1)
		line = ft_next_pipe(line + 1);
	return (out);
}

t_dlist	*ft_get_pipes_list(char *line, char **argv, char **envp)
{
	t_dlist	*out;
	t_cmd	*cmd;
	char	*p;

	if (ft_pipes_count(line) == 0)
		return (NULL);
	line = ft_next_pipe(line);
	out = NULL;
	while (line)
	{
		*line++ = 0;
		p = ft_next_pipe(line);
		cmd = ft_fill_cmd(line, argv, envp);
		ft_dlstadd_back(&out, ft_dlstnew(cmd));
		line = p;
	}
	return (out);
}
