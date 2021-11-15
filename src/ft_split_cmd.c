/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:28:27 by mehill            #+#    #+#             */
/*   Updated: 2021/11/15 22:54:38 by mehill           ###   ########.fr       */
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

// added () for spliting 
char	*ft_next_sep(char *line)
{
	int		prth;
	int		qts;

	qts = 0;
	prth = 0;
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
		{
			if (qts == 0)
				qts = *line;
			else if (qts == *line)
				qts = 0;
		}
		else if (qts == 0 && *line == '(' && *(line - 1) != '\\')
			prth++;
		else if (qts == 0 && prth > 0 && *line == ')' && *(line - 1) != '\\')
			prth--;
		else if (qts == 0 && prth == 0 && *(line - 1) != '\\' && ft_isspace(*line))
			return (line);
		line++;
	}
	return (NULL);
}

int	ft_arg_count(char *line)
{
	int		out;

	out = 0;
	while (*line && ft_isspace(*line))
		line++;
	while (line && *line)
	{
		line = ft_next_sep(line);
		while (line && *line && ft_isspace(*line))
			line++;
		out++;
	}
	return (out);
}

char	**ft_split_args(char *line)
{
	char	**out;
	char	*save;
	char	*p;
	int		w;

	save = ft_strdup(line);
	line = save;
	out = malloc((ft_arg_count(line) + 1) * sizeof(char *));
	if (out == NULL)
		return (NULL);
	w = 0;
	while (line && *line && ft_isspace(*line))
		line++;
	while (line && *line)
	{
		p = ft_next_sep(line);
		if (p)
			*p++ = 0;
		out[w++] = ft_strdup(line);
		line = p;
		while (line && *line && ft_isspace(*line))
			line++;
	}
	out[w] = NULL;
	free(save);
	return (out);
}
