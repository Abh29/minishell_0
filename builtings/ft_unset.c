/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:14:10 by ddelena           #+#    #+#             */
/*   Updated: 2022/03/04 02:32:24 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

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

void	remove_elem_from_envp(t_list **env, char *key, char **env_line)
{
    t_list	*res;


    res = ft_lstpop_find(env, key);
    if (res)
    {
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

int ft_unset2(t_list **env, char **env_line, char **argv)
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
    g_msh.envp = list_to_array(*env);
	ft_set_envp();
    return (1);
}

void	ft_unset(t_cmd *cmd)
{
	(void) cmd;
	exit(0);
}
