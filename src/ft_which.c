/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_which.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelena <ddelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 23:19:04 by mehill            #+#    #+#             */
/*   Updated: 2022/02/23 19:14:28 by ddelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

//TODO: add builtings !!
static char	*ft_check_possible(char	**paths, char *scmd)
{
	char	*pcmd;

	pcmd = NULL;
	while (*paths)
	{
		pcmd = ft_strjoin(*(paths++), scmd);
		if (access(pcmd, F_OK | X_OK) == 0)
			break ;
		free(pcmd);
		pcmd = NULL;
	}
	return (pcmd);
}

//////////my_code/////////

/////////unset///////////

int	ft_keylen(char *keyval)
{
    int	i;

    i = 0;
    while (keyval[i] && keyval[i] != '=')
        i++;
    return (i);
}

t_list	*ft_lstpop_find(t_list **lst, char *key)
{
    t_list	*elem;
    t_list	*curr;

    elem = NULL;
    curr = *lst;
    if (curr && !ft_strncmp(curr->content, key, ft_keylen(key)))
    {
        elem = curr;
        *lst = elem->next;
        elem->next = NULL;
        return (elem);
    }
    while (curr && curr->next)
    {
        if (!ft_strncmp(curr->next->content, key, ft_keylen(key)))
        {
            elem = curr->next;
            curr->next = curr->next->next;
            elem->next = NULL;
            break ;
        }
        curr = curr->next;
    }
    return (elem);
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

void	*memory_error(size_t size)
{
    void	*ptr;

    ptr = malloc(size);
    if (!ptr)
    {
        ft_putendl_fd("Critical error: cannot allocate memory", 2);
        exit(errno);
    }
    else
        return (ptr);
}

char	**ft_lst_get_array(t_list *lst)
{
    int		size_array;
    char	**arr;

    size_array = ft_lstsize(lst) + 1;
    arr = memory_error(sizeof(*arr) * size_array);
    if (!arr)
        return (NULL);
    arr[--size_array] = NULL;
    while (lst)
    {
        arr[--size_array] = ft_strdup(lst->content);
        lst = lst->next;
    }
    return (arr);
}

void	free_lst(t_list **lst)
{
    if (lst)
    {
        free((*lst)->content);
        free(lst);
    }
}

void	remove_elem_from_envp(t_list **env, char *key, char **env_line)
{
    t_list	*res;

    res = ft_lstpop_find(env, key);
    if (res)
    {
        printf("res content %s\n", (char *)res->content);
        //ft_split_free(env_line);
        //free_lst(&res);
        free(res->content);
        free(res);
        env_line = ft_lst_get_array(*env);
    }
}

char **list_to_array(t_list *env)
{
    char **out;
    int i;

    i = 0;
    out = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
    if (!out)
        ft_exit("Error : Unable to allocate memory for env!\n", 1);
    while (env)
    {
        out[i] = ft_strdup(env->content);
        i++;
        env = env->next;
    }
    return (out);
}

int ft_unset(t_list **env, char **env_line, char **argv)
{
    t_list *dup_env;
    int     i;
    extern t_global g_msh;

    i = 1;
    dup_env = *env;
    if (argv[1] == NULL)
        return (1);
    while (argv[i])
    {
        dup_env = *env;
        while (dup_env && dup_env->next)
        {
            if (argv[i][0] != '\0')
            {
                remove_elem_from_envp(env, argv[i], env_line);
            }
            dup_env = dup_env->next;
        }
        i++;
    }
   // ft_free_split(&g_msh.envp);
    g_msh.envp = list_to_array(*env);
    return (1);
}

/////////unset///////////

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

t_list *init_env(char **envp)
{
    t_list *env;

    env = NULL;
    while (*envp)
    {
//        ft_lstadd_front(&env, ft_lstnew(ft_strdup(*envp++)));
        ft_lstadd_back(&env, ft_lstnew(ft_strdup(*envp++)));
    }
   return (env);
}

int check_if_builtin(char *name)
{
	if (!ft_strncmp(name, "echo", ft_strlen(name)) || !ft_strncmp(name, "unset", ft_strlen(name)) || !ft_strncmp(name, "env", ft_strlen(name)) || //
       !ft_strncmp(name, "exit", ft_strlen(name)) || !ft_strncmp(name, "cd", ft_strlen(name)) || !ft_strncmp(name, "pwd", ft_strlen(name)) || //
       !ft_strncmp(name, "export", ft_strlen(name)))
       return (1);
   return (0);
}

int	print_error(void)
{
    ft_putstr_fd(strerror(errno), 2);
    write(2, "\n", 2);
    return (1);
}

int ft_pwd(void)
{
    //if dir == NULL -> errno
    // On successful completion, this function returns 0. Otherwise,
    // it returns a system error code (errno).

    char *buf;

    buf = ft_calloc(4096, 1);
    if (getcwd(buf, 4096))
    {
        ft_putstr_fd(buf, 1);
        free(buf);
        write(1, "\n", 1);
        return (0);
    }
    else
    {
        print_error();
        free(buf);
        return (1);
    }
}

int ft_echo(int argc, char **argv)
{
    int flag;
    int i;
	(void)argv;
	(void)argc;
    flag = 0;
    i = 1;
    if (argv[i])
    {
        if (argv[1] && !ft_strncmp("-n", argv[1], 2))
           flag = 1;
        while (argv[i])
        {
            if (ft_strncmp("-n", argv[i], 2))
            {
                ft_putstr_fd(argv[i], 1);
                if (i != argc- 1)
                    write(1, " ", 1);
            }
            i++;
        }
    }
    if (!flag )
        write(1, "\n", 1);
    return (0);
}


int ft_env(t_list *env)
{
    t_list *dup_env;

    printf("\n!!!!\n");

    dup_env = env;
    printf("\n\nbuilting env\n\n");
    while (dup_env)
    {
        printf("%s\n", dup_env->content);
        dup_env = dup_env->next;
    }
    
   /* while (dup_env->next)
    {
        if (ft_strrchr(dup_env->content, '='))
        {
            ft_putstr_fd(dup_env->content, 1);
            ft_putstr_fd("\n", 1);
        }
        dup_env = dup_env->next;
    }
    if (ft_strrchr(dup_env->content, '='))
    {
        ft_putstr_fd(dup_env->content, 1);
        ft_putstr_fd("\n", 1);
    }*/
    return (0);
}


void run_builtin(char **envp, t_cmd *cmd_struct, char *cmd, char **argv)
{
	extern t_global g_msh;
    t_list *env;
    char **env_line;
	
    env = init_env(envp);
    env_line = ft_lst_get_array(env);
	int status;
	(void)env;
	(void)env_line;
	(void)envp;
	(void)cmd_struct;
	(void)cmd;
    (void)argv;
	status = 0;
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
       status = ft_echo(g_msh.argc, argv);
    // else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
    //    status = ft_pwd(); - done?
    //else if (!ft_strncmp(name, "exit", ft_strlen(name)))
    //    status = ft_exit(argv);
    else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
       status = ft_env(env);
    else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
       status = ft_unset(&env, env_line, argv);
    //    - where to change envp
    
}

void is_builtin(char **envp, char *cmd, t_cmd *cmd_struct, char **argv)
{
	if (check_if_builtin(cmd))
		run_builtin(envp, cmd_struct, cmd, argv);
}

char	*ft_which(char	*cmd, char **envp, t_cmd *cmd_struct, char **argv)
{
	char	**paths;
	char	*scmd;
	char	*pcmd;

	if (!cmd || !envp || !(*envp))
		return (NULL);
		(void)cmd_struct;
	is_builtin(envp, cmd, cmd_struct, argv);
    // printf("%d\n", *cmd_struct->exit_stat);
	scmd = ft_strjoin("/", cmd);
	paths = ft_split(getenv("PATH"), ':');
	pcmd = ft_check_possible(paths, scmd);
	ft_free_split(&paths);
	free(scmd);
	scmd = NULL;
	if (pcmd == NULL)
		return (ft_strdup(cmd));
	// check for access
	return (pcmd);
}
