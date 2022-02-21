#include "../libft/libft.h"
#include <errno.h>

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

void	free_lst(t_list *lst)
{
    if (lst)
    {
        free(lst->content);
        free(lst);
    }
}


void	remove_elem_from_envp(t_list *env, char *key, char **env_line)
{
    t_list	*res;

    res = ft_lstpop_find(&env, key);
    if (res)
    {
        ft_split_free(env_line);
        free_lst(res);
        env_line = ft_lst_get_array(env);
    }
}

int ft_unset(char **envp, t_list *env, char **env_line, char **argv)
{
    t_list *dup_env;
    int     i;

    i = 1;
    dup_env = env;
    if (argv[1] == NULL)
        return (1);
    while (argv[i])
    {
        dup_env = env;
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
    return (1);
}
