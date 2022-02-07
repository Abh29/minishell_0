#include "../mch.h"

void ft_redirect(t_cmd *cmd)
{
	char	*line;
	int		n;

	if (cmd->red->fdin == 0 && cmd->red->fdout == 1 && cmd->red->limiter == NULL)
		return ;	// no redirections
	if (cmd->red->fdin < 0 || cmd->red->fdout < 0)
		exit(1);
	if (cmd->red->limiter)
	{
		if (pipe(cmd->in_out) < 0)
			ft_exit("coult not creat a pipe for redirection !\n", 1);
		n = fork();
		if (n < 0)
			ft_exit("Error : coult not fork process for redirection !\n", 1);
		if (n == 0)
		{
			n = ft_strlen(cmd->red->limiter);
			cmd->red->limiter[n] = '\n';
			while (1)
			{
				ft_putstr_fd("> ", STDOUT_FILENO);
				line = get_next_line(STDIN_FILENO);
				if (!line || ft_strncmp(cmd->red->limiter, line, n + 1) == 0)
					break ;
				ft_putstr_fd(line, cmd->in_out[1]);
				free(line);
			}
			free(line);
			close(cmd->in_out[0]);
			close(cmd->in_out[1]);
			exit(0);
		}
		dup2(cmd->in_out[0], STDIN_FILENO);
		close(cmd->in_out[0]);
		close(cmd->in_out[1]);
		while(wait(NULL) > 0);
	}
	else if (cmd->red->fdin != 0)
		dup2(cmd->red->fdin, STDIN_FILENO);
	if (cmd->red->fdout != 1)
		dup2(cmd->red->fdout, STDOUT_FILENO);
}

void ft_execute_simple_cmd(t_cmd *cmd)
{
	ft_redirect(cmd);
	execv(cmd->cmd_name, cmd->args);
	exit(1); //case of error !
}

void ft_create_pipes(t_cmd *cmd, int pipes[][2])
{
	t_dlist *lpipe;
	int		i;

	i = 0;
	lpipe = cmd->pipe;
	if (ft_dlstsize(lpipe) >= MAX_PIPE)
		ft_exit("Pipe Error : number of pipes more than MAX_PIPE supported !\n", 2);
	while (i < MAX_PIPE)
	{
		if (pipe(pipes[i++]) < 0)
			ft_exit("Pipe Error : coult not create a pipe !\n", 1);
	}
}

void ft_close_pipes(int pipesfds[][2])
{
	int		i;

	i = 0;
	while (i < MAX_PIPE)
	{
		close(pipesfds[i][0]);
		close(pipesfds[i][1]);
		i++;
	}
}

void ft_print_pipe(t_cmd *cmd)
{
	t_dlist *p;
	t_cmd	*c;
	int		i;

	printf("pipe size %d\n", ft_dlstsize(cmd->pipe));
	printf("cmd 0 : %s %s\n", cmd->cmd_name, cmd->args[1]);
	p = cmd->pipe;
	i = 1 ;
	while (p)
	{
		c = p->content;
		printf("cmd %i : %s %s\n", i++, c->cmd_name, c->args[1]);
		p = p->next;
	}
}

void ft_proc0(t_cmd *cmd, int pipefds[][2])
{
	int	pid;

	pid = fork();
    if (pid < 0)
        ft_exit("Fork Error!", 1);
    if (pid == 0)
    {
        dup2(pipefds[0][1], STDOUT_FILENO);
		ft_close_pipes(pipefds);
		ft_execute_simple_cmd(cmd);
        perror("Error in process exec ");
       	exit(3);
    }
}

void	ft_proci(t_cmd *cmd, int pipefds[][2], int i)
{
	int	pid;

	pid = fork();
    if (pid < 0)
        ft_exit("Fork Error!", 1);
    if (pid == 0)
    {
        dup2(pipefds[i - 1][0], STDIN_FILENO);
        dup2(pipefds[i][1], STDOUT_FILENO);
		ft_close_pipes(pipefds);
		ft_execute_simple_cmd(cmd);
        perror("Error in process exec ");
       	exit(3);
    }
}

int	ft_procn(t_cmd *cmd, int pipefds[][2], int n)
{
	int	pid;

	pid = fork();
    if (pid < 0)
        ft_exit("Fork Error!", 1);
    if (pid == 0)
    {
        dup2(pipefds[n - 1][0], STDIN_FILENO);
		ft_close_pipes(pipefds);
		ft_execute_simple_cmd(cmd);
        perror("Error in process exec ");
       	exit(1);
    }
	return (pid);
}


void ft_pipe_cmd(t_cmd *cmd)
{
	t_dlist *pipel;
	int		pipefds[MAX_PIPE][2];
	int		i;
	int		ret;
	int		last_pid;

	//ft_print_pipe(cmd);
	ft_create_pipes(cmd, pipefds);
	pipel = cmd->pipe;
	ft_proc0(cmd, pipefds);
	i = 1;
	while (pipel->next)
	{
		ft_proci(pipel->content, pipefds, i);
		i++;
		pipel = pipel->next;
	}
	last_pid = ft_procn(pipel->content, pipefds, i);
	ft_close_pipes(pipefds);
	waitpid(last_pid, &i, 0);
	ret = WEXITSTATUS(i);
	while (wait(&i) > 0);
	exit(ret);
}


int	ft_execute_defined_cmd(t_cmd *cmd, int *ret)
{
	int							pid;
	int							status;

	pid = fork();
	if (pid < 0)
		ft_exit("Error : fork error !\n", 1);
	if (pid == 0)
	{
		if (cmd->cmd_name == NULL)
			ft_exit("Error : Command not found !\n", 1);
		if (cmd->pipe)
			ft_pipe_cmd(cmd);
		else
			ft_execute_simple_cmd(cmd);
		exit(1);
	}
	while (wait(&status) > 0);
	*ret = WEXITSTATUS(status);
	return (pid);
}

int ft_execute_cmd(t_cmd *cmd, int *ret)
{
	t_dlist	*and_ors;
	t_cmd	*tmpc;
	int		pid;

	and_ors = cmd->ands_ors;
	pid = ft_execute_defined_cmd(cmd, ret);
	while(and_ors)
	{
		tmpc = and_ors->content;
		if(ret == 0 && tmpc->log == AND)
			pid = ft_execute_defined_cmd(tmpc, ret);
		else if (ret != 0 && tmpc->log == OR)
			pid = ft_execute_defined_cmd(tmpc, ret);
		and_ors = and_ors->next;
	}
	return (pid);
}
