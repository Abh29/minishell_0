#include "../mch.h"

//TODO: split by logical operators.
int	ft_islogical_op(char *line)
{
	if (*line == '|' && *line++)
		if (*line == '|')
			return (1);
	if (*line == '&' && *line++)
		if (*line == '&')
			return (1);
	return (0);
}

char	*ft_next_logical_op(char *line)
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
		else if (qts == 0 && prth == 0 && *(line - 1) != '\\' && \
		ft_islogical_op(line))
			return (line);
		line++;
	}
	return (NULL);
}

int	ft_op_count(char *line)
{
	int	out;

	out = 0;
	line = ft_next_logical_op(line);
	while (line && ++out)
		line = ft_next_logical_op(line + 2);
	return (out);
}

t_dlist	*ft_get_ands_ors_list(char *line, char **argv, char **envp)
{
	t_dlist	*out;
	t_cmd	*cmd;
	char	*p;
	int		log;

	if (ft_op_count(line) == 0)
		return (NULL);
	out = NULL;
	line = ft_next_logical_op(line);
	while (line)
	{
		if (*(line + 1) == '&')
			log = 1;
		else
			log = 2;
		*line++ = 0;
		*line++ = 0;
		p = ft_next_logical_op(line);
		if (p)
			*p = 0;
		cmd = ft_fill_cmd(line, argv, envp);
		cmd->log = log;
		ft_dlstadd_back(&out, ft_dlstnew(cmd));
		line = p;
	}
	return (out);
}
