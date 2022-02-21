#include "../libft/libft.h"

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
