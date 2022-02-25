/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:14:06 by ddelena           #+#    #+#             */
/*   Updated: 2022/02/26 02:12:58 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

static void	ft_put_str_until_chr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		write(1, &str[i], 1);
		i++;
	}
}

static void	ft_put_str_after_chr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i])
	{
		i++;
		ft_putstr_fd(&str[i], 1);
	}
}

void	print_export(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_put_str_until_chr(env[i], '=');
		if (ft_strrchr(env[i], '='))
		{
			write(1, "=", 1);
			write(1, "\"", 1);
			ft_put_str_after_chr(env[i], '=');
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		i++;
	}
}


int	ft_write_error_export(char *exp)
{
	write(2, "export: '", 10);
	write(2, exp, ft_strlen(exp));
	write(2, "': not a valid identifier\n", 26);
	return (1);
}

static int	my_str_cmp(void *s1, void *s2)
{
	char	*one;
	char	*two;
	int		i;

	one = (char *)s1;
	two = (char *)s2;
	i = 0;
	while (one[i] == two[i] && two[i] && one[i])
		i++;
	if (one[i] == two[i])
		return (0);
	return (one[i] - two[i]);
}

void	sort_the_envp(t_global *g_msh, int len_env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < len_env)
	{
		j = 0;
		while (j < len_env - 1)
		{
			if (my_str_cmp(g_msh->envp[j], g_msh->envp[j + 1]) > 0)
			{
				tmp = g_msh->envp[j];
				g_msh->envp[j] = g_msh->envp[j + 1];
				g_msh->envp[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	check_export(char *exp)
{
	int	i;

	i = 0;
	if (exp[0] == '=' || ft_isdigit(exp[0]) || !ft_isalpha(exp[0]))
		return (ft_write_error_export(exp));
	while (exp[i] && exp[i] != '=')
	{
		if (!ft_isalpha(exp[i]) && !ft_isdigit(exp[i]))
			return (ft_write_error_export(exp));
		i++;
	}
	return (0);
}

char	*ft_strdub_chr(char *str, char c, int *flag)
{
	char	*new_str;
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] != '=')
		*flag = 0;
	new_str = ft_calloc(i + 1, sizeof(char));
	if (new_str == NULL)
		exit(errno);
	i = 0;
	while (str[i] && str[i] != c)
	{
		new_str[i] = str[i];
		i++;
	}
	return (new_str);
}

int	ft_export(t_cmd *cmd, t_list **env, char **env_line, t_global *g_msh)
{
	int	i;
	int	ret_vel;

	i = 1;
	ret_vel = 0;
	if (ft_split_len(cmd->args) == 1)
	{
		sort_the_envp(g_msh, ft_split_len(g_msh->envp));
		print_export(g_msh->envp);
		ft_set_envp();
		return (ret_vel);
	}
	while (cmd->args[i])
	{
		if (!check_export(cmd->args[i]))
			g_msh->envp = insert_or_update_elem_from_envp(g_msh, env, cmd->args[i], env_line);
		else
			ret_vel = 1;
		i++;
	}
	ft_set_envp();
	return (ret_vel);
}
