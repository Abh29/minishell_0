/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:15:56 by mehill            #+#    #+#             */
/*   Updated: 2022/02/26 02:58:36 by mehill           ###   ########.fr       */
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
	g_msh.envp = ft_vectdup(envp);
	g_msh.ret = malloc(sizeof(int));
	g_msh.buff_idx = 0;
	g_msh.envp_fd = -1;
	ft_set_envp();
}

void	ft_set_envp(void)
{
	int			i;

	i = 0;
	g_msh.envp_fd = open("./.__envp__", O_CREAT | O_RDWR | O_TRUNC, 0775);
	while (g_msh.envp[i])
	{
		write(g_msh.envp_fd, g_msh.envp[i], ft_strlen(g_msh.envp[i]));
		write(g_msh.envp_fd, "\n", 1);
		i++;
	}
	close(g_msh.envp_fd);
}

void	ft_get_envp(void)
{
	char		*line;
	int			i;
	extern char	**environ;

	g_msh.envp_fd = open("./.__envp__", O_RDONLY, 775);
	i = 0;
	line = get_next_line(g_msh.envp_fd);
	while (line)
	{
		line[ft_strlen(line) - 1] = 0;
		if (g_msh.envp[i])
			free(g_msh.envp[i]);
		g_msh.envp[i++] = line;
		line = get_next_line(g_msh.envp_fd);
	}
	close(g_msh.envp_fd);
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
	close(g_msh.envp_fd);
	return (0);
}
