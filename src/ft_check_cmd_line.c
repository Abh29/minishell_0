/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_cmd_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 19:07:08 by mehill            #+#    #+#             */
/*   Updated: 2021/12/05 20:23:29 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

/*	unclosed quotes				3
	unclosed parenthes			4
	wrong	parenthese order	5
	unexpected token after  ><  6
	unexpected token after  |&	7
	unexpected syntax at 0		8
	add ...
*/

int	ft_qts_helper(char c, int *qts)
{
	if (c == '\'' || c == '\"')
	{
		if (*qts == 0)
			*qts = c;
		else if (*qts == c)
			*qts = 0;
		return (1);
	}
	return (0);
}

int	ft_check_parnth(char *line, int *pos)
{
	int	prth;
	int	qts;

	prth = 0;
	*pos = 0;
	while (*line)
	{
		if (ft_qts_helper(*line, &qts))
			(void) pos;
		else if (qts == 0 && *line == '(')
			prth++;
		else if (qts == 0 && *line == ')')
			prth--;
		if (prth < 0)
			return (5);
		(*pos)++;
		line++;
	}
	if (prth > 0)
		return (4);
	return (0);
}

int	ft_check_quts(char *line, int *pos)
{
	int	qts;
	int	i;

	i = 0;
	qts = 0;
	*pos = 0;
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
		{
			if (qts == 0)
			{
				qts = *line;
				(*pos) = i;
			}
			else if (qts == *line)
				qts = 0;
		}
		i++;
		line++;
	}
	if (qts != 0)
		return (3);
	return (0);
}

void	ft_check_cmd_line(char *line, int *err, int *pos)
{
	if (line == NULL || err == NULL || pos == NULL)
		return ;
	*err = -1;
	*err = ft_check_quts(line, pos);
	if (*err == 0)
		*err = ft_check_parnth(line, pos);
	if (*err == 0)
		*err = ft_check_anomal_0(line, pos);
	if (*err == 0)
		*err = ft_check_anomal_1(line, pos);
	if (*err == 0)
		*err = ft_check_anomal_2(line, pos);
}
