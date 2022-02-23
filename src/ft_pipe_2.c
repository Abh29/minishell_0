/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:33:24 by mehill            #+#    #+#             */
/*   Updated: 2022/02/23 21:34:07 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

void	ft_pipe_cmd(t_cmd *cmd)
{
	t_dlist	*pipel;
	int		pipefds[MAX_PIPE][2];
	int		i;
	int		ret;
	int		last_pid;

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
	while (wait(&i) > 0)
		(void) i;
	exit(ret);
}
