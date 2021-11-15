#include "../mch.h"

char	*ft_next_or(char *line)
{
	while (line && *line)
	{
		line = ft_next_logical_op(line + 1);
		if (line && *line == '|')
			return (line);
	}
	return (NULL);
}

int	ft_ors_count(char *line)
{
	int	out;

	out = 0;
	if (line)
		line = ft_next_or(line);
	while (line && ++out)
		line = ft_next_or(line + 2);
	return (out);
}

t_dlist	*ft_get_ors_list(char *line, char **argv, char **envp)
{
	t_dlist	*out;
	t_dlist	*ands;
	t_cmd	*cmd;
	char	*p;

	if (ft_ors_count(line) == 0)
		return (NULL);
	out = NULL;
	while (line)
	{
		line = line + 2;
		p = ft_next_or(line);
		if (p)
		{
			*p = 0;
			*(p + 1) = 0;
		}
		ands = ft_get_ands_list(line, argv, envp);
		cmd = ft_fill_cmd(line, argv, envp);
		cmd->ands = ands;
		ft_dlstadd_back(&out, ft_dlstnew(cmd));
		line = p;
	}
	return (out);
}
