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

t_dlist	*ft_get_astrix_matches(char *line)
{
	t_dlist			*out;
	DIR				*d;
	struct dirent	*dir;
	char			*p;

	p = ft_last_slash(line);
	if (ft_next_astrix(p) == NULL)
		return (NULL);
	if (p == line && *p != '/')
		line = ft_strdup(".");
	else
		line = ft_substr(line, 0, p - line + 1);
	d = opendir(line);
	out = NULL;
	if (d)
	{
		dir = readdir(d);
		while (dir)
		{
			if (ft_match_astrix(p + 1, dir->d_name))
				ft_dlstadd_back(&out, ft_dlstnew(ft_strjoin(line, \
				dir->d_name)));
			dir = readdir(d);
		}
		closedir(d);
	}
	free(line);
	return (out);
}
