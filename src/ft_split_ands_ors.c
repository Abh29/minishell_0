/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ands_ors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 20:32:18 by mehill            #+#    #+#             */
/*   Updated: 2021/12/05 20:36:30 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

//TODO: split by logical operators.
int	ft_islogical_op(char *line)
{
	if (*line == '|' && *line++)
		if (*line == '|')
			return (1);
	if (*line == '&' && *line++)
		if (*line == '&')
			return (1);
	return (0);
}

char	*ft_next_logical_op(char *line)
{
	int		prth;
	int		qts;
	char	prev;

	qts = 0;
	prth = 0;
	prev = 0;
	while (*line)
	{
		if (ft_qts_helper(*line, &qts))
			(void)qts;
		else if (qts == 0 && *line == '(' && prev != '\\')
			prth++;
		else if (qts == 0 && prth > 0 && *line == ')' && prev != '\\')
			prth--;
		else if (qts == 0 && prth == 0 && prev != '\\' && \
		ft_islogical_op(line))
			return (line);
		prev = *line;
		line++;
	}
	return (NULL);
}

int	ft_op_count(char *line)
{
	int	out;

	out = 0;
	line = ft_next_logical_op(line);
	while (line && ++out)
		line = ft_next_logical_op(line + 2);
	return (out);
}

void	ft_set_log(char *line, int *log)
{
	if (*(line + 1) == '&')
		*log = 1;
	else
		*log = 2;
}

t_dlist	*ft_get_ands_ors_list(char *line, char **argv, char **envp)
{
	t_dlist	*out;
	t_cmd	*cmd;
	char	*p;
	int		log;

	if (ft_op_count(line) == 0)
		return (NULL);
	out = NULL;
	line = ft_next_logical_op(line);
	while (line)
	{
		ft_set_log(line, &log);
		*line++ = 0;
		*line++ = 0;
		p = ft_next_logical_op(line);
		if (p)
			*p = 0;
		cmd = ft_fill_cmd(line, argv, envp);
		cmd->log = log;
		ft_dlstadd_back(&out, ft_dlstnew(cmd));
		line = p;
	}
	return (out);
}
