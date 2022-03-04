/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:19:33 by mehill            #+#    #+#             */
/*   Updated: 2022/03/05 00:17:33 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

void	execute_cmd_list(t_dlist *cmds)
{
	extern t_global	g_msh;
	int				status;

	status = 0;
	while (cmds)
	{
		g_msh.pid_fg = ft_execute_cmd(cmds->content, g_msh.ret);
		cmds = cmds->next;
		while (wait(&status) > 0)
			(void) status;
		ft_get_envp();
	}
}

void	ft_execute_builting(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->builting == FT_ENV)
		ft_env();
	else if (cmd->builting == FT_UNSET)
		ft_unset(cmd);
	else if (cmd->builting == FT_ECHO)
		ft_echo(cmd);
	else if (cmd->builting == FT_CD)
		ft_cd(cmd);
	else if (cmd->builting == FT_PWD)
		ft_pwd();
	else if (cmd->builting == FT_EXPORT)
		ft_export(cmd);
	else if (cmd->builting == FT_SUBSHELL)
		ft_subshell(cmd);
}

void	ft_execute_simple_cmd(t_cmd *cmd)
{
	extern t_global	g_msh;

	ft_redirect(cmd);
	ft_get_envp();
	if (cmd->builting == FT_NULL)
	{
		if (access(cmd->cmd_name, F_OK | X_OK) == 0)
			execve(cmd->cmd_name, cmd->args, g_msh.envp);
		else
			perror(cmd->cmd_name);
	}
	else
		ft_execute_builting(cmd);
	exit(1);
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
	while (wait(&status) > 0)
		(void) status;
	*ret = WEXITSTATUS(status);
	return (pid);
}

int	ft_execute_cmd(t_cmd *cmd, int *ret)
{
	t_dlist	*and_ors;
	t_cmd	*tmpc;
	int		pid;

	and_ors = cmd->ands_ors;
	pid = ft_execute_defined_cmd(cmd, ret);
	while (and_ors)
	{
		tmpc = and_ors->content;
		if (*ret == 0 && tmpc->log == AND)
			pid = ft_execute_defined_cmd(tmpc, ret);
		else if (*ret != 0 && tmpc->log == OR)
			pid = ft_execute_defined_cmd(tmpc, ret);
		and_ors = and_ors->next;
	}
	return (pid);
}
