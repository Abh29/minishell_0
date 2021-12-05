/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 19:06:16 by mehill            #+#    #+#             */
/*   Updated: 2021/12/05 20:15:52 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

char	*ft_get_next_dollar(char *str)
{
	int	q;

	q = 0;
	while (*str)
	{
		if (*str == '\'')
		{
			if (q == 0)
				q = *str;
			else
				q = 0;
		}
		else if (q == 0 && *str == '$')
			return (str);
		str++;
	}
	return (NULL);
}

int	ft_var_length(char *line)
{
	int	out;

	if (line && *line == '$')
		line++;
	out = 0;
	while (line && *line)
	{
		if (ft_strchr(" \"\'$()", *line))
			break ;
		out++;
		line++;
	}
	return (out);
}

char	*ft_helper_1(char **p)
{
	char	*var;

	var = getenv(*p);
	if (var == NULL)
		var = ft_strdup("");
	else
		var = ft_strdup(var);
	free(*p);
	return (var);
}

char	*ft_expand_dollar(char *line)
{
	char	*out;
	char	*p;
	char	*var;

	out = ft_strdup(line);
	line = ft_get_next_dollar(out);
	while (line)
	{
		p = ft_substr(line, 1, ft_var_length(line));
		if (p == NULL)
			p = ft_strdup("");
		else if (ft_strncmp(p, "?", 1) == 0)
			var = ft_get_last_exit_status(NULL);
		else
			var = ft_helper_1(&p);
		p = ft_replace_word(out, var, line - out, ft_var_length(line) + 1);
		free(var);
		free(out);
		out = p;
		line = ft_get_next_dollar(out);
	}
	return (out);
}
