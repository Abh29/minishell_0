#include "../mch.h"

// FIXME: derefrencing of (line - 1)!
char	*ft_get_next_cemicln(char *line)
{
	char	qts;
	int		prth;

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
		else if (qts == 0 && prth == 0 && *(line - 1) != '\\' && *line == ';')
			return (line);
		line++;
	}
	return (NULL);
}

// TODO: cmd == NULL ??
t_dlist	*ft_get_cmd_list(char *line, char **argv, char **envp)
{
	char	*cmdline;
	char	*smq;
	t_dlist	*out;
	t_cmd	*cmd;

	smq = ft_get_next_cemicln(line);
	cmdline = NULL;
	out = NULL;
	cmd = NULL;
	while (smq)
	{
		*smq = 0;
		cmdline = ft_strdup(line);
		line = smq + 1;
		cmd = ft_fill_cmd(cmdline, argv, envp);
		ft_dlstadd_back(&out, ft_dlstnew(cmd));
		free(cmdline);
		cmdline = NULL;
		smq = ft_get_next_cemicln(line);
	}
	if (*line)
	{
		cmd = ft_fill_cmd(line, argv, envp);
		ft_dlstadd_back(&out, ft_dlstnew(cmd));
	}
	return (out);
}

void	ft_free_cmd_list(t_dlist **cmds)
{
	t_dlist	*p;

	if (cmds == NULL || *cmds == NULL)
		return ;
	while (*cmds)
	{
		p = *cmds;
		*cmds = p->next;
		ft_free_cmd((t_cmd **) &(p->content));
		free(p);
	}
}
