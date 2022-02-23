/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:31:25 by mehill            #+#    #+#             */
/*   Updated: 2022/02/23 21:35:36 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

void	ft_create_pipes(t_cmd *cmd, int pipes[][2])
{
	t_dlist	*lpipe;
	int		i;

	i = 0;
	lpipe = cmd->pipe;
	if (ft_dlstsize(lpipe) >= MAX_PIPE)
		ft_exit("Pipe Error : number of pipes more than MAX_PIPE !\n", 2);
	while (i < MAX_PIPE)
	{
		if (pipe(pipes[i++]) < 0)
			ft_exit("Pipe Error : coult not create a pipe !\n", 1);
	}
}

void	ft_close_pipes(int pipesfds[][2])
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

void	ft_proc0(t_cmd *cmd, int pipefds[][2])
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
