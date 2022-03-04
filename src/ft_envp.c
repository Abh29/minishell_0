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

	i = 0;
	g_msh.envp_fd = open("/tmp/.__envp__", O_CREAT | O_RDWR | O_TRUNC, 0775);
	while (g_msh.envp[i])
	{
		//printf("*****%s\n", g_msh.envp[i]);
		write(g_msh.envp_fd, g_msh.envp[i], ft_strlen(g_msh.envp[i]));
		write(g_msh.envp_fd, "\n", 1);
		i++;
	}
	close(g_msh.envp_fd);
}

void	ft_get_envp(void)
{
	char			*line;
	int				i;
	extern t_global	g_msh;

	g_msh.envp_fd = open("/tmp/.__envp__", O_RDONLY, 775);
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

char	*ft_getenv(char *key)
{
	extern t_global	g_msh;
	char			**sep;
	char			*out;
	int				i;

	if (key == NULL)
		return (NULL);
	ft_get_envp();
	printf("ft_get_env\n");
	i = 0;
	while (g_msh.envp[i] && ft_strchr(g_msh.envp[i], '='))
	{
		printf(".");
		sep = ft_split(g_msh.envp[i], '=');
		if (sep[0] && sep[1])
		{
			if (ft_strncmp(sep[0], key, ft_strlen(key)) == 0)
			{
				out = ft_strdup(sep[1]);
				ft_free_split(&sep);
				return (out);
			}
		}
		ft_free_split(&sep);
		i++;
	}
	return (NULL);
}

void	ft_setenv(char *key, char *val)
{
	char			*env;
	char			*newenv;
	int				i;
	char			**new_envp;
	extern t_global	g_msh;

	printf("ft_setenv() key = %s  value = %s\n", key, val);
	if (key == NULL || val == NULL)
		return ;
	i = 0;
	printf("here\n");
	env = ft_getenv(key);
	printf("this the search result env = %s\n", env);
	if (env)
	{
		while (g_msh.envp[i] && ft_strncmp(key, g_msh.envp[i], ft_strlen(key)))
			i++;
		newenv = ft_strjoin(key, "=");
		key = ft_strjoin(newenv, val);
		if (key)
		{
			free(g_msh.envp[i]);
			g_msh.envp[i] = key;
		}
		free(env);
		free(newenv);
	}
	else
	{
		while (g_msh.envp[i])
			i++;
		new_envp = malloc((i + 2) * sizeof(char *));
		if (new_envp == NULL)
			return ;
		i = 0;
		while (g_msh.envp[i])
		{
			new_envp[i] = g_msh.envp[i];
			i++;
		}
		key = ft_strjoin(key, "=");
		new_envp[i++] = ft_strjoin(key, val);
		new_envp[i] = NULL;
		free(key);
		free(g_msh.envp);
		g_msh.envp = new_envp;
		printf("new env =%s\n", new_envp[i - 1]);
	}
}
