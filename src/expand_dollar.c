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

char	*ft_replace_word(char *str, char *word, char *start, char *end)
{
	char	*out;

	*start = 0;
	start = ft_strjoin(str, word);
	if (!start)
		return (ft_strjoin(str, end));
	out = ft_strjoin(start, end);
	free(start);
	return (out);
}

char	*ft_expand_one_dollar(char *arg)
{
	char	*v_name;
	char	*p;
	char	*start;
	char	*end;
	char	*out;

	start = ft_get_next_dollar(arg);
	end = start + 1;
	while (*end)
	{
		if (ft_strchr(" \"\'$", *end))
			break ;
		end++;
	}
	p = ft_substr(start, 1, end - start - 1);
	if (ft_strncmp(p, "?", 1) == 0)
		v_name = ft_get_last_exit_status(NULL);
	else
		v_name = getenv(p);
	free(p);
	out = ft_replace_word(arg, v_name, start, end);
	if (out == NULL)
		return (ft_strdup(arg));
	return (out);
}

char	*ft_expand_dollar(char *arg)
{
	char	*out;
	char	*save;
	char	*p;

	save = NULL;
	p = ft_get_next_dollar(arg);
	out = ft_strdup(arg);
	while (p)
	{
		save = ft_expand_one_dollar(out);
		free(out);
		out = ft_strdup(save);
		free(save);
		p = ft_get_next_dollar(out);
	}
	return (out);
}

void	ft_shift_left(char	*arr)
{
	while (*arr)
	{
		*arr = *(arr + 1);
		arr++;
	}
	return ;
}

void	ft_skip_char(char *str, char *c)
{
	if (str == NULL || c == NULL)
		return ;
	while (*str)
	{
		if (str == c)
		{
			ft_shift_left(str);
			return ;
		}
		str++;
	}
}
