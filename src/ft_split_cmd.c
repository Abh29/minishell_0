/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:28:27 by mehill            #+#    #+#             */
/*   Updated: 2021/10/29 21:34:14 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

// dont forget skipped quotes

int	ft_valid_sep(int current, int previous, int *quote)
{
	//printf("%c%d|", current, *quote);
	if (*quote == -1 && previous != '\\' && ft_strchr(" \t\n", current))
		return (1);
	if (*quote != -1 && current == *quote && previous != '\\')
	{
		*quote = -1;
		return (0);
	}
	if (*quote == -1 && previous != '\\' \
	&& (current == '\"' || current == '\''))
		*quote = current;
	return (0);
}

int	ft_arg_count(char *line)
{
	int	out;
	int	qts;
	int	prev;

	out = 1;
	qts = -1;
	prev = 0;
	while (*line)
	{
		printf("%c%d|", *line, ft_valid_sep(*line, prev, &qts));
		if (ft_valid_sep(*line, prev, &qts))
		{
			if (*(line + 1) && !ft_valid_sep(*(line + 1), *line, &qts))
				out++;
		}
		prev = *line;
		line++;
	}
	return (out);
}

char	**ft_split_cmd(char *line)
{
	(void) line;
	return (NULL);
		/*	while (*line && ft_valid_sep(*line, prev, &qts))
			prev = *line++;
		if (*line)
		{
			prev = *(line++);
			if (*line)
				out++;
		}
		while (*line && ft_valid_sep(*line, prev, &qts) == 0)
			prev = *line++;
		if (*line)
			line++;*/
}
