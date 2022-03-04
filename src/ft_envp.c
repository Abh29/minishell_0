/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 00:57:37 by mehill            #+#    #+#             */
/*   Updated: 2022/03/04 02:52:48 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

void	ft_set_envp(void)
{
	int				i;
	extern t_global	g_msh;
	char			*size;

	i = 0;
	g_msh.envp_fd = open("/tmp/.__envp__", O_CREAT | O_RDWR | O_TRUNC, 0775);
	if (g_msh.envp_fd < 0)
		ft_exit("Error : couldn't open envp file !\n", 1);
	while (g_msh.envp[i])
		i++;
	size = ft_itoa(i);
	write(g_msh.envp_fd, size, ft_strlen(size));
	write(g_msh.envp_fd, "\n", 1);
	free(size);
	i = 0;
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
	char			*line;
	char			*size;
	int				i;
	extern t_global	g_msh;
	char			**new_env;

	i = 0;
	g_msh.envp_fd = open("/tmp/.__envp__", O_RDONLY, 775);
	size = get_next_line(g_msh.envp_fd);
	if (size && ft_atoi(size) > i)
	{
		new_env = ft_calloc(ft_atoi(size) + 1, sizeof(char *));
		if (g_msh.envp == NULL)
			ft_exit("Error : coult not allocate memory for envp !\n", 1);
		line = get_next_line(g_msh.envp_fd);
		while (line)
		{
			line[ft_strlen(line) - 1] = 0;
			new_env[i++] = line;
			line = get_next_line(g_msh.envp_fd); 
		}
		new_env[i] = NULL;
		ft_free_split(&g_msh.envp);
		g_msh.envp = new_env;
	}
	close(g_msh.envp_fd);
}
