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

char	*ft_getenv(char *key)
{
	extern t_global	g_msh;
	char			**sep;
	char			*out;
	int				i;

	if (key == NULL)
		return (NULL);
	ft_get_envp();
	i = 0;
	while (g_msh.envp[i] && ft_strchr(g_msh.envp[i], '='))
	{
		sep = ft_split(g_msh.envp[i], '=');
		if (sep[0] && sep[1])
		{
			if (ft_strncmp(sep[0], key, ft_strlen(sep[0])) == 0)
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

int		ft_updatenv(char *key, char *val)
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

	if (key == NULL || val == NULL)
		return ;
	i = 0;
	if (ft_updatenv(key, val) == 0)
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

int		ft_dellenv(char *key)
{
	char			*env;
	int				i;
	extern t_global	g_msh;

	if (key == NULL || *key == 0)
		return (0);
	i = 0;
	env = ft_getenv(key);
	if (env)
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
		if (env)
			free(env);
		return (1);
	}
	return (0);
}
