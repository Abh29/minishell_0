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

int	ft_isspace(int c)
{
	if (c == ' ' || (c > 8 && c < 14))
		return (1);
	return (0);
}

int	ft_valid_sep(int current, int previous, int *quote)
{
	if (*quote == -1 && previous != '\\' && ft_isspace(current))
		return (1);
	if (*quote != -1 && current == *quote && previous != '\\')
		*quote = -1;
	else if (*quote == -1 && previous != '\\' \
	&& (current == '\"' || current == '\''))
		*quote = current;
	return (0);
}

int	ft_arg_count(char *line)
{
	int	out;
	int	qts;
	int	prev;

	out = 0;
	qts = -1;
	prev = 0;
	while (*line && ft_isspace(*line))
		line++;
	while (*line)
	{
		while (*line && ft_valid_sep(*line, prev, &qts))
		{
			prev = *line;
			line++;
		}
		if (*line)
		{
			prev = *line;
			line++;
			out++;
		}
		while (*line && ft_valid_sep(*line, prev, &qts) == 0)
		{
			prev = *line;
			line++;
		}
	}
	return (out);
}

char	**ft_split_args(char *line)
{
	int		i;
	char	**out;
	char	prev;
	int		qts;
	int		w;
	int		j;

	out = malloc((ft_arg_count(line) + 1) * sizeof(char *));
	if (out == NULL)
		return (NULL);
	qts = -1;
	prev = 0;
	w = 0;
	while (*line)
	{
		while (*line && ft_valid_sep(*line, prev, &qts))
		{
			prev = *line;
			line++;
		}
		if (*line)
		{
			i = 1;
			prev = *line;
			line++;
			while (*line && ft_valid_sep(*line, prev, &qts) == 0 && i++ > -1)
			{
				prev = *line;
				line++;	
			}
			out[w] = malloc(i + 1);
			line -= i;
			j = 0;
			while (j < i)
				out[w][j++] = *line++;
			out[w++][i] = 0;			
		}
	}
	out[w] = NULL;
	return (out);
}
