/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:14:06 by ddelena           #+#    #+#             */
/*   Updated: 2022/03/04 03:02:08 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

void	ft_sort_env(char **arr, int (*f)(const char *, const char *, size_t))
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			if (f(arr[i], arr[j], ft_strlen(arr[i])) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	ft_export(t_cmd *cmd)
{
	int				i;
	char			*p;
	char			**cpy;
	extern t_global	g_msh;

	i = 1;
	ft_get_envp();
	if (cmd->args[1] == NULL)
	{
		cpy = ft_vectdup(g_msh.envp);
		ft_sort_env(cpy, ft_strncmp);
		while (cpy[i])
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(cpy[i], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
			i++;
		}
		ft_free_split(&cpy);
	}
	else
	{
		while (cmd->args[i])
		{
			if (ft_strlen(cmd->args[i]) == 0 || cmd->args[i][0] == '=')
				ft_exit("Error : not a valid indentifier for export !\n", 1);
			p = ft_strchr(cmd->args[i], '=');
			if ((!p || *(p + 1) == 0) && i++)
				continue ;
			*p = 0;
			ft_setenv(cmd->args[i], p + 1);
			ft_set_envp();
			i++;
		}
	}
	exit(0);
}
