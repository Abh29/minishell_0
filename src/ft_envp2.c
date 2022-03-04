/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 00:57:37 by mehill            #+#    #+#             */
/*   Updated: 2022/03/05 00:32:55 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

char	*ft_getenv(char *key)
{
	extern t_global	g_msh;
	int				i;
	int				size;

	if (key == NULL)
		return (NULL);
	ft_get_envp();
	i = 0;
	key = ft_strjoin(key, "=");
	size = ft_strlen(key);
	while (key && g_msh.envp[i])
	{
		if (ft_strncmp(key, g_msh.envp[i], size) == 0)
		{
			free(key);
			return (ft_strdup(g_msh.envp[i] + size));
		}
		i++;
	}
	return (NULL);
}

int	ft_updatenv(char *key, char *val)
{
	char			*env;
	char			*newenv;
	int				i;
	extern t_global	g_msh;

	if (key == NULL || val == NULL)
		return (0);
	i = 0;
	env = ft_getenv(key);
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
		return (1);
	}
	return (0);
}

void	ft_setenv(char *key, char *val)
{
	int				i;
	char			**new_envp;
	extern t_global	g_msh;

	i = 0;
	if (key && val && ft_updatenv(key, val) == 0)
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
	}
}

int	ft_dellenv(char *key)
{
	char			*env;
	int				i;
	extern t_global	g_msh;

	i = 0;
	env = ft_getenv(key);
	if (key && *key && env)
	{
		free(env);
		key = ft_strjoin(key, "=");
		while (g_msh.envp[i] && ft_strncmp(key, g_msh.envp[i], ft_strlen(key)))
			i++;
		env = g_msh.envp[i];
		while (g_msh.envp[i] && g_msh.envp[i + 1])
		{
			g_msh.envp[i] = g_msh.envp[i + 1];
			i++;
		}
		g_msh.envp[i] = NULL;
		free(key);
		free(env);
		return (1);
	}
	return (0);
}
