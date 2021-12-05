/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:28:27 by mehill            #+#    #+#             */
/*   Updated: 2021/12/05 20:41:10 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

char	*ft_next_sep(char *line)
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
			(void)line;
		else if (qts == 0 && *line == '(' && prev != '\\')
			prth++;
		else if (qts == 0 && prth > 0 && *line == ')' && prev != '\\')
			prth--;
		else if (qts == 0 && prth == 0 && prev != '\\' && ft_isspace(*line))
			return (line);
		prev = *line;
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

void	ft_helper_4(char **line, char **out, int w)
{
	char	*p;

	p = ft_next_sep(*line);
	if (p)
		*p++ = 0;
	out[w] = ft_strdup(*line);
	*line = p;
}

char	**ft_split_args(char *line)
{
	char	**out;
	char	*save;
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
		ft_helper_4(&line, out, w++);
		while (line && *line && ft_isspace(*line))
			line++;
	}
	out[w] = NULL;
	free(save);
	return (out);
}
