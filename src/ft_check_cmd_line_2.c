/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_cmd_line_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 19:28:38 by mehill            #+#    #+#             */
/*   Updated: 2022/02/23 21:39:33 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

char	*ft_next_accepted_char(char *line, char *exept)
{
	if (line == NULL)
		return (NULL);
	while (*line && ft_isspace(*line))
		line++;
	if (*line == 0 || ft_strchr(exept, *line))
		return (NULL);
	return (line);
}

int	ft_check_anomal_0(char *line, int *pos)
{
	(void)pos;
	if (ft_strrchr("&|;,", *line))
		return (8);
	return (0);
}

int	ft_check_anomal_1(char *line, int *pos)
{
	int	qts;

	qts = 0;
	while (*line)
	{
		if (ft_qts_helper(*line, &qts))
			(void) pos;
		else if (qts == 0 && *line == '>')
		{
			if (*(line + 1) == '>')
				line++;
			if (ft_next_accepted_char(line + 1, "><|&-;,") == NULL)
				return (6);
		}
		else if (qts == 0 && *line == '<')
		{
			if (*(line + 1) == '<')
				line++;
			if (ft_next_accepted_char(line + 1, "><|&-;,") == NULL)
				return (6);
		}
		(*pos)++;
		line++;
	}
	return (0);
}

int	ft_check_anomal_2(char *line, int *pos)
{
	int	qts;

	*pos = 0;
	while (*line)
	{
		if (ft_qts_helper(*line, &qts))
			(void) pos;
		else if (qts == 0 && *line == '&')
		{
			if (*(line + 1) != '&')
				return (7);
			line++;
			if (ft_next_accepted_char(line + 1, "><|&-") == NULL)
				return (6);
		}
		else if (qts == 0 && *line == '|')
		{
			if (*(line + 1) == '|')
				line++;
			if (ft_next_accepted_char(line + 1, "><|&-") == NULL)
				return (7);
		}
		(*pos)++;
		line++;
	}
	return (0);
}
