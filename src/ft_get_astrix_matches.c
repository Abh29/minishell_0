/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_astrix_matches.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 20:17:24 by mehill            #+#    #+#             */
/*   Updated: 2021/12/05 20:23:28 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

char	*ft_next_slash(char *str)
{
	int	q;

	q = 0;
	if (*str == '/')
		return (str);
	str++;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			if (q == 0)
				q = *str;
			else if (q == *str)
				q = 0;
		}
		else if (q == 0 && *str == '/' && *(str - 1) != '\\')
			return (str);
		str++;
	}
	return (NULL);
}

char	*ft_next_astrix(char *str)
{
	int	q;

	q = 0;
	if (*str == '*')
		return (str);
	str++;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			if (q == 0)
				q = *str;
			else if (q == *str)
				q = 0;
		}
		else if (q == 0 && *str == '*' && *(str - 1) != '\\')
			return (str);
		str++;
	}
	return (NULL);
}

char	*ft_last_slash(char *str)
{
	char	*p;

	if (str == NULL || *str == 0)
		return (NULL);
	p = ft_next_slash(str);
	while (p)
	{
		str = p;
		p = ft_next_slash(str + 1);
	}
	return (str);
}

void	ft_helper_3(DIR *d, char *p, char *line, t_dlist **out)
{
	struct dirent	*dir;

	dir = readdir(d);
	if (*p == '/')
		p++;
	while (dir)
	{
		if (ft_match_astrix(p, dir->d_name))
			ft_dlstadd_back(out, ft_dlstnew(ft_strjoin(line, \
			dir->d_name)));
		dir = readdir(d);
	}
}

t_dlist	*ft_get_astrix_matches(char *line)
{
	t_dlist			*out;
	DIR				*d;
	char			*p;

	p = ft_last_slash(line);
	if (ft_next_astrix(p) == NULL || *line == '-')
		return (NULL);
	if (p == line && *p != '/')
		line = ft_strdup("./");
	else
		line = ft_substr(line, 0, p - line + 1);
	d = opendir(line);
	out = NULL;
	if (d)
	{
		ft_helper_3(d, p, line, &out);
		closedir(d);
	}
	free(line);
	return (out);
}
