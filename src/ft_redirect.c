/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:34:42 by mehill            #+#    #+#             */
/*   Updated: 2022/02/23 21:35:11 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

void	ft_redirect(t_cmd *cmd)
{
	char	*line;
	int		n;

	if (cmd->red->fdin == 0 && cmd->red->fdout == 1 \
	&& cmd->red->limiter == NULL)
		return ;
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
		while (wait(NULL) > 0)
			(void) n;
	}
	else if (cmd->red->fdin != 0)
		dup2(cmd->red->fdin, STDIN_FILENO);
	if (cmd->red->fdout != 1)
		dup2(cmd->red->fdout, STDOUT_FILENO);
}
