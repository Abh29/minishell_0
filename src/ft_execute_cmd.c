/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:19:33 by mehill            #+#    #+#             */
/*   Updated: 2022/02/23 21:35:23 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

void	ft_execute_builting(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->builting == FT_ENV)
		ft_env(cmd);
	else if (cmd->builting == FT_UNSET)
		ft_unset(cmd);
	else if (cmd->builting == FT_ECHO)
		ft_echo(cmd);
	else if (cmd->builting == FT_CD)
		ft_cd(cmd);
	else if (cmd->builting == FT_PWD)
		ft_pwd(cmd);
	else if (cmd->builting == FT_EXPORT)
		ft_export(cmd);
	else if (cmd->builting == FT_SUBSHELL)
		ft_subshell(cmd);
}

void	ft_execute_simple_cmd(t_cmd *cmd)
{
	ft_redirect(cmd);
	if (cmd->builting == FT_NULL)
		execv(cmd->cmd_name, cmd->args);
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
