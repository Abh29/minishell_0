#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"
# include <unistd.h>
# include <sys/errno.h>


// to-do: cd(fails), export✔✔, *unset✔, *exit✔, *env✔

int status;

void ft_envp(char **envp, t_list *env)
{
    t_list *dup_env;

    dup_env = env;
    while (dup_env->next)
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
    }
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


char	**ft_lst_get_array(t_list *lst)
{
    int		size_array;
    char	**arr;

    size_array = ft_lstsize(lst) + 1;
    arr = ft_malloc_x(sizeof(*arr) * size_array);
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

t_list *init_env(char **envp, t_list *env)
{
    while (*envp)
    {
//        ft_lstadd_front(&env, ft_lstnew(ft_strdup(*envp++)));
        ft_lstadd_back(&env, ft_lstnew(ft_strdup(*envp++)));
//        printf("%s\n", (char *)env->content);
    }
   return (env);
}

int is_builtin(char *name)
{
    if (!ft_strncmp(name, "echo", ft_strlen(name)) || !ft_strncmp(name, "unset", ft_strlen(name)) || !ft_strncmp(name, "env", ft_strlen(name)) //
        !ft_strncmp(name, "exit", ft_strlen(name)) || !ft_strncmp(name, "cd", ft_strlen(name)) || !ft_strncmp(name, "pwd", ft_strlen(name)) //
        !ft_strncmp(name, "export", ft_strlen(name)))
        return (1);
    return (0);
}

int run_builtin(char *name)
{
    if (!ft_strncmp(name, "echo", ft_strlen(name)))
        status = ft_echo(msh, cmnd->arg, msh->env);
    else if (!ft_strncmp(name, "unset", ft_strlen(name)))
        status = ft_unset(cmnd->arg, msh);
    else if (!ft_strncmp(name, "env", ft_strlen(name)))
        status = ft_env(cmnd->arg, msh->env, msh);
    else if (!ft_strncmp(name, "exit", ft_strlen(name)))
        status = ft_exit(cmnd->arg, msh);
    else if (!ft_strncmp(name, "cd", ft_strlen(name)))
        status = ft_cd(cmnd->arg, msh);
    else if (!ft_strncmp(name, "pwd", ft_strlen(name)))
        status = ft_pwd();
    else if (!ft_strncmp(name, "export", ft_strlen(name)))
        status = ft_export(cmnd->arg, msh);
    return (status);
}
void ft_export(char **envp, char **argv, int argc);
int ft_unset(char **envp, t_list *env, char **env_line, char **argv);

int main(int argc, char **argv, char **envp)
{
    t_list *env;
    char **env_line;

    env = init_env(envp, env);
    env_line = ft_lst_get_array(env);
    if (is_builtin(argv[1])
    {
        run_builtin(argv[1]);
        exit(status);
    }
//    while (env->next)
//    {
//        printf("%s\n", (char *)env->content);
//        env = env->next;
//    }
//    ft_unset(envp, env, env_line, argv);
//    ft_envp(envp, env);
//        ft_echo(argc, argv);
//    ft_pwd();
//    ft_export(envp, argv, argc);
}