#include "../mch.h"

char	*ft_valid_red(char *arg)
{
	int	q;

	if (arg == NULL)
		return (NULL);
	q = 0;
	while (*arg)
	{
		if (*arg == '\'' || *arg == '\"')
		{
			if (q == 0)
				q = *arg;
			else
				q = 0;
		}
		else if (q == 0 && (*arg == '>' || *arg == '<'))
			return (arg);
		arg++;
	}
	return (NULL);
}

void	ft_helper_out(t_io_red *red, char *r, char *next)
{
	char	*out;

	if (*r == 0)
	{
		if (ft_valid_red(next))
			out = ft_substr(next, 0, ft_valid_red(next) - next);
		else
			out = ft_strdup(next);
	}
	else
	{
		if (ft_valid_red(r + 1))
			out = ft_substr(r, 0, ft_valid_red(r) - r);
		else
			out = ft_strdup(r);
	}
	if (red->fdout > 1)
		close(red->fdout);
	if (red->append)
		red->fdout = open(out, O_WRONLY | O_CREAT | O_APPEND, 0755);
	else
		red->fdout = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (red->fdout < 0)
		perror("Error : ");
	free(out);
}

void	ft_get_redout(t_io_red *red, char **args)
{
	char	*r;

	while (*args)
	{
		r = ft_valid_red(*args);
		while (r)
		{
			if (*r == '>' && r++)
			{
				if (*r == '>' && r++)
					red->append = 1;
				else
					red->append = 0;
				ft_helper_out(red, r, *(args + 1));
			}
			r = ft_valid_red(r + 1);
		}
		args++;
	}
}
