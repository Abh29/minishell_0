/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:15:56 by mehill            #+#    #+#             */
/*   Updated: 2022/02/23 21:58:40 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mch.h"

t_global	g_msh;

void	execute_cmd_list(t_dlist *cmds)
{
	int	status;

	while (cmds)
	{
		g_msh.pid_fg = ft_execute_cmd(cmds->content, g_msh.ret);
		cmds = cmds->next;
		while (wait(&status) > 0)
			(void) status;
		*g_msh.ret = WEXITSTATUS(status);
	}
}

void	init_global_msh(int argc, char **argv, char **envp)
{
	g_msh.argc = argc;
	g_msh.argv = argv;
	g_msh.envp = envp;
	g_msh.ret = malloc(sizeof(int));
	g_msh.buff_idx = 0;
}

void	handle_sigint(int sig)
{
	(void)sig;
	if (g_msh.pid_fg != 0)
		kill(g_msh.pid_fg, sig);
	g_msh.buff_idx = 0;
	ft_reset_input_buff();
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(SHELL_NAME, 1);
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	int		status;
	t_dlist	*lst;

	init_global_msh(argc, argv, envp);
	signal(SIGINT, handle_sigint);
	g_msh.line = NULL;
	while (1)
	{
		g_msh.pid_fg = 0;
		if (g_msh.line)
			free(g_msh.line);
		g_msh.line = ft_get_cmd_line(1);
		if (!g_msh.line || ft_strncmp(g_msh.line, "exit\n", 5) == 0)
			break ;
		if (*g_msh.line == '\n' || *g_msh.line == '\t')
			continue ;
		g_msh.line[ft_strlen(g_msh.line) - 1] = 0;
		lst = ft_get_cmd_list(g_msh.line, argv, envp);
		execute_cmd_list(lst);
		while (wait(&status) > 0)
			(void) status;
		ft_free_cmd_list(&lst);
	}
	if (g_msh.line)
		free(g_msh.line);
	return (0);
}
