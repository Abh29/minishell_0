#include "../mch.h"

char	*ft_get_next_cemicln(char *line)
{
	char	q;

	q = 0;
	while (*line)
	{
		if (q != 0 && *line == q)
			q = 0;
		else if (q == 0 && (*line == '\'' || *line == '\"'))
			q = *line;
		else if (q == 0 && *line == ';')
			return (line);
		line++;
	}
	return (NULL);
}

t_cmd	*ft_fill_cmd(char *line, char **argv, char **envp)
{
	t_cmd	*cmd;
	char	**spt;

	spt = ft_split_args(line);
	printf("this is the received line %s\n", line);
	ft_print_splt(spt, 1);
	getchar();
	cmd = ft_new_cmd();
	cmd->cmd_name = ft_which(spt[0], envp);
	ft_get_redctn(cmd->red, spt);
	cmd->envp = ft_vectdup(argv);
	cmd->args = ft_vectdup(spt);
	ft_free_split(&spt);
	return (cmd);
}

// cmd == NULL ??
t_dlist	*ft_get_cmd_list(char *line, char **argv, char **envp)
{
	char	*cmdline;
	char	*smq;
	t_dlist	*out;
	t_cmd	*cmd;

	smq = ft_get_next_cemicln(line);
	cmdline = NULL;
	out = NULL;
	while (smq)
	{
		*smq = 0;
		cmdline = ft_strdup(line);
		line = smq + 1;
		printf("this is cmdline : %s\n", cmdline);
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
