/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:13:58 by ddelena           #+#    #+#             */
/*   Updated: 2022/02/26 01:38:18 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

int	ft_split_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

t_list	*ft_lstfind(t_list *env,  char *key)
{
	size_t	key_len;
	int cont;
	key_len = ft_keylen(key);
	while (env)
	{
		cont = ((int *)env->content)[key_len];
		if (!ft_strncmp(env->content, key, key_len))
			break ;
		env = env->next;
	}
	return (env);
}

char	*get_val_from_keyval(char *keyval)
{
	size_t	len_key;

	if (!keyval)
		return (ft_strdup(""));
	len_key = ft_keylen(keyval);
	if (len_key && keyval[len_key] == '=')
		return (ft_strdup(keyval + ft_keylen(keyval) + 1));
	return (ft_strdup(""));
}

char	*get_value_from_envp(t_cmd *cmd, char *key, t_global *g_msh, t_list **env)
	
{
	(void)cmd;
	(void)g_msh;
	(void)env;
	
	t_list	*res;
	res = ft_lstfind(*env, key);
	if (res)
		return (get_val_from_keyval(res->content));
	return (ft_strdup(""));
}

void	ft_split_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	print_errno(void)
{
	ft_putstr_fd(strerror(errno), 2);
	write(2, "\n", 2);
	return (1);
}

int	chdir_error(char *dir)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(dir, 2);
	ft_putstr_fd(": ", 2);
	return (print_errno());
}

void	ft_lstdelone2(t_list *lst)
{
	if (lst)
	{
		free(lst->content);
		free(lst);
	}
}

char **insert_or_update_elem_from_envp(t_global *g_msh, t_list **env, char *keyval, char **env_line)
{
	(void)g_msh;
	remove_elem_from_envp(env, keyval, env_line);
	ft_lstadd_front(env, ft_lstnew(ft_strdup(keyval)));
	ft_split_free(env_line);
	char **line = ft_lst_get_array(*env);

	return (line);

}

int	set_new_oldpwd(char *pwd_old, t_global *g_msh, t_list **env, char **env_line)
{
	char	*pwd;

	pwd = ft_strjoin("OLDPWD=", pwd_old);
	g_msh->envp = insert_or_update_elem_from_envp(g_msh, env, pwd, env_line);
	free(pwd);
	return (0);
}

void	*ft_malloc_x(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_putendl_fd("Critical error: cannot allocate memmory", 2);
		exit(errno);
	}
	else
		return (ptr);
}

int	set_new_pwd(t_global *g_msh, t_list **env, char **env_line)
{
	char	*new_pwd;
	char	*tmp;
	char	*pwd;

	(void)g_msh;
	(void)env;
	(void)env_line;

	tmp = ft_malloc_x(1024);
	pwd = getcwd(tmp, 1024);
	if (pwd == NULL)
	{
		free(tmp);
		return (print_errno());
	}
	new_pwd = ft_strjoin("PWD=", pwd);
	g_msh->envp = insert_or_update_elem_from_envp(g_msh, env, new_pwd, env_line);

	free(new_pwd);
	free(tmp);
	return (0);
}

int	help_change_dir(char *oldpwd, char *dir, t_global *g_msh, t_list **env, char **env_line)
{
	if (chdir(dir) == -1)
		return (chdir_error(dir));
	if (oldpwd)
		if (set_new_oldpwd(oldpwd, g_msh, env, env_line) != 0)
			return (print_errno());
	if (set_new_pwd(g_msh, env, env_line) != 0)
		return (print_errno());
	return (0);
}

int	change_dir(char *dir, t_global *g_msh, t_list **env, char **env_line)
{
	char	*oldpwd;
	char	*tmp;
	int		ret_v;

	tmp = ft_calloc(1024, 1);
	if (!tmp)
		print_errno();
	oldpwd = getcwd(tmp, 1024);
	ret_v = help_change_dir(oldpwd, dir, g_msh, env, env_line);
	free(tmp);
	return (ret_v);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}


int	cd_to_oldpwd(t_cmd *cmd, t_global *g_msh, t_list **env, char **env_line)
{
	char	*oldpwd;
	int		r_vel;

	oldpwd = get_value_from_envp(cmd, "OLDPWD", g_msh, env);
	
	if (oldpwd[0] == '\0')
	{
		ft_putstr_fd("minishell: cd : HOME not set \n", 2);
		return (1);
	}
	r_vel = change_dir(oldpwd, g_msh, env, env_line);
	free(oldpwd);
	return (r_vel);
}

int	change_work_dir(t_global *g_msh, t_list **env, char **env_line, t_cmd *cmd)
{
	char	*argb[2];

	if (ft_strcmp(cmd->args[1], "-") == 0)
		return (cd_to_oldpwd(cmd, g_msh, env, env_line));
	if (ft_strcmp(cmd->args[1], "~") == 0)
	{
		argb[0] = "cd";
		argb[1] = NULL;
		return (ft_cd(cmd, env, env_line, g_msh));
	}
	return (change_dir(cmd->args[1], g_msh, env, env_line));
}


int	ft_cd(t_cmd *cmd, t_list **env, char **env_line, t_global *g_msh)
{
	(void)cmd;
	(void)env;
	(void)env_line;
	char	*home;
	int		r_vel;

	if (ft_split_len(cmd->args) == 1)
	{
		home = get_value_from_envp(cmd, "HOME", g_msh, env);
		r_vel = change_dir(home, g_msh, env, env_line);
		free(home);
		return (r_vel);
	}
	if (ft_split_len(cmd->args) == 2)
	{
		return (change_work_dir(g_msh, env, env_line, cmd));
	}
	return (0);
}
