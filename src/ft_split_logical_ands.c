#include "../mch.h"

char	*ft_next_and(char *line)
{
	while (line && *line)
	{
		line = ft_next_logical_op(line + 1);
		if (line && *line == '&')
			return (line);
	}
	return (NULL);
}

int	ft_ands_count(char *line)
{
	int	out;

	out = 0;
	line = ft_next_and(line);
	while (line && ++out)
		line = ft_next_and(line + 2);
	return (out);
}

t_dlist	*ft_get_ands_list(char *line, char **argv, char **envp)
{
	t_dlist	*out;
	t_dlist	*pipes;
	t_cmd	*cmd;
	char	*p;

	if (ft_ands_count(line) == 0)
		return (NULL);
	out = NULL;
	line = ft_next_and(line);
	while (line)
	{
		line = line + 2;
		p = ft_next_and(line);
		if (p)
		{
			*p = 0;
			*(p + 1) = 0;
		}
		pipes = ft_get_pipes_list(line, argv, envp);
		cmd = ft_fill_cmd(line, argv, envp);
		cmd->pipe = pipes;
		ft_dlstadd_back(&out, ft_dlstnew(cmd));
		line = p;
	}
	return (out);
}
