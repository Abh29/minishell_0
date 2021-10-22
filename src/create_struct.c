#include "../mch.h"

t_io_red	*ft_new_io_red(void)
{
	t_io_red	*out;

	out = malloc (sizeof(t_io_red));
	if (out == NULL)
		return (NULL);
	out->fdin = 0;
	out->fdout = 1;
	out->fderr = 2;
	out->limiter = NULL;
	out->append = 0;
	return (out);
}

t_cmd	*ft_new_cmd(void)
{
	t_cmd	*out;

	out = malloc(sizeof(t_cmd));
	out->cmd_name = NULL;
	out->args = NULL;
	out->envp = NULL;
	*(out->exit_stat) = -1;
	out->ors = NULL;
	out->ands = NULL;
	out->pipe = NULL;
	return (out);
}

void	ft_free_io_red(t_io_red **red)
{
	if ((*red)->limiter)
		free((*red)->limiter);
	free(*red);
	*red = NULL;
}

//free envp??
void	ft_free_cmd(t_cmd **cmd)
{
	free((*cmd)->cmd_name);
	ft_free_split(&(*cmd)->args);
	ft_free_split(&(*cmd)->envp);
	ft_free_io_red(&(*cmd)->red);
	while ((*cmd)->ors)
	{
		ft_free_cmd((t_cmd **) &(*cmd)->ors->content);
		(*cmd)->ors = (*cmd)->ors->next;
	}
	while ((*cmd)->ands)
	{
		ft_free_cmd((t_cmd **) &(*cmd)->ands->content);
		(*cmd)->ands = (*cmd)->ands->next;
	}
	if ((*cmd)->pipe)
	{
		ft_free_cmd((t_cmd **) &(*cmd)->ands->content);
		(*cmd)->ands = (*cmd)->ands->next;
	}
	free(*cmd);
	*cmd = NULL;
}
