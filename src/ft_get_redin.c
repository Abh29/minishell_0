#include "../mch.h"

char	*ft_helper_in(t_io_red *red, char *r, char *next)
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
	if (red->fdin > 0)
		close(red->fdout);
	return (out);
}

void	ft_get_redin(t_io_red *red, char **args)
{
	char	*r;
	char	*in;

	while (*args)
	{
		r = ft_valid_red(*args);
		while (r)
		{
			if (*r == '<' && r++)
			{
				if (*r == '<' && r++)
					red->limiter = ft_helper_in(red, r, *(args + 1));
				else
				{
					in = ft_helper_in(red, r, *(args + 1));
					red->fdin = open(in, O_RDONLY, 0755);
					if (red->fdin < 0)
						perror("Error : ");
					free(in);
				}
			}
			r = ft_valid_red(r + 1);
		}
		args++;
	}
}

void	ft_get_redctn(t_io_red *red, char **args)
{
	if (red == NULL || args == NULL || *args == NULL)
		return ;
	ft_get_redin(red, args);
	ft_get_redout(red, args);
	errno = 0;
}
