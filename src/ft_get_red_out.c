/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_red_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 20:29:07 by mehill            #+#    #+#             */
/*   Updated: 2021/12/05 20:29:07 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

char	*ft_next_red_out(char *line)
{
	int	q;

	q = 0;
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
		{
			if (q == 0)
				q = *line;
			else if (q == *line)
				q = 0;
		}
		else if (q == 0 && *line == '>')
			return (line);
		line++;
	}
	return (NULL);
}

int	ft_red_out_length(char *line)
{
	int	out;
	int	qt;

	while (line && *line == '>')
		line++;
	while (*line && ft_isspace(*line))
		line++;
	out = 0;
	qt = 0;
	while (line && *line)
	{
		if (*line == '\'' || *line == '\"')
		{
			if (qt == 0)
				qt = *line;
			else if (qt == *line)
				qt = 0;
		}
		else if (qt == 0 && (ft_isspace(*line) || ft_strchr("><", *line)))
			break ;
		out++;
		line++;
	}
	return (out);
}

char	*ft_get_out_name(char *line, int *t)
{
	char	*p;
	char	*out;
	int		i;

	p = ft_next_red_out(line);
	out = NULL;
	while (p)
	{
		*t = 0;
		i = ft_red_out_length(p);
		*p++ = ' ';
		if (*p == '>' && (*t)++ > -1)
			*p++ = ' ';
		while (*p && ft_isspace(*p))
			p++;
		if (out)
			free(out);
		out = ft_substr(p, 0, i);
		while (*p && i-- > -1)
			*p++ = ' ';
		p = ft_next_red_out(line);
	}
	return (out);
}

//TODO: test this !;
void	ft_fill_out_redirection(t_io_red *red, char *line)
{
	char	*name;
	char	*p;
	int		t;

	p = ft_next_red_out(line);
	if (p == NULL)
		return ;
	name = ft_get_out_name(line, &t);
	if (name == NULL)
		ft_exit("Error : couldn't get redirection var!\n", 1);
	if (t == 1)
	{
		red->fdout = open(name, O_WRONLY | O_CREAT | O_APPEND, 0755);
		red->append = 1;
	}
	else
		red->fdout = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (red->fdout < 0)
		perror("Error : ");
	free(name);
}
