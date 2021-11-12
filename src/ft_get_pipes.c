#include "../mch.h"

char	*ft_next_pipe(char *str)
{
	int	q;

	q = 0;
	if (*str)
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
		else if (q == 0 && *str == '|' && *(str - 1) != '\\')
			return (str);
		str++;
	}
	return (NULL);
}

int	ft_pipes_count(char *line)
{
	int	out;

	out = 0;
	line = ft_next_pipe(line);
	while (line && ++out)
		line = ft_next_pipe(line);
	return (out);
}

t_dlist	*ft_get_pipes_list(char *line, char **argv, char **envp)
{
	t_dlist	*out;
	t_cmd	*cmd;
	char	*p;

	if (ft_pipes_count(line) == 0)
		return (NULL);
	line = ft_next_pipe(line);
	out = NULL;
	while (line)
	{
		p = ft_next_pipe(line++);
		if (p)
			*p++ = 0;
		cmd = ft_fill_cmd(line, argv, envp);
		ft_dlstadd_back(&out, ft_dlstnew(cmd));
		line = p;
	}
	return (out);
}
