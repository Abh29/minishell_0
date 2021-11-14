#include "../mch.h"

//TODO: split by logical operators.
int	ft_islogical_op(*line)
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
		else if (qts == 0 && prth == 0 && *(line - 1) != '\\' && ft_islogical_op(*line))
			return (line);
		line++;
	}
	return (NULL);
}
