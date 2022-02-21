#include "../libft/libft.h"

int status;

char *check_envp()

int	find_size(char **argv)
{
    int	i;

    i = 0;
    if (argv == NULL)
        return (0);
    while (argv[i])
        i++;
    return (i);
}

int	find_len(char **arr)
{
    int	i;

    i = 0;
    while (arr[i])
        i++;
    return (i);
}


int	check_param(char *argv)
{
    int	i;
    int	flag;

    flag = 0;
    i = 0;
    if (argv[i] == '+' || argv[i] == '-')
    {
        flag = 1;
        i++;
    }
    if ((int)ft_strlen(argv) > 21 + flag)
        return (1);
    while (argv[i])
    {
        if (ft_isdigit(argv[i]) == 0)
            return (1);
        i++;
    }
    return (0);
}

void no_params(char *argv)
{
    ft_putstr_fd("exit: ", 2);
    ft_putstr_fd(argv, 2);
    ft_putstr_fd(": numeric argument required", 2);
    ft_putstr_fd("\n", 2);
    exit(255);
//    return (255);
}

int	extra_param(void)
{
    ft_putstr_fd("exit: ", 2);
    ft_putstr_fd("too many arguments", 2);
    ft_putstr_fd("\n", 2);
    return (1);
}

unsigned int	ft_atoi(const char *str)
{
    int			i;
    int			minus;
    u_int64_t	num;

    i = 0;
    minus = 1;
    num = 0;
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            minus = -1;
        i++;
    }
    while (str[i])
        num = (num * 10) + (str[i++] - '0');
    return (num * minus);
}


int do_exit(char **argv)
{
    if (argv[1] == NULL)
    {
        exit(status);
        //must be an old status
    }
    if (check_param(argv[1]))
        return (no_params(argv[1]));
    if (find_len(argv) > 2)
        return (extra_param();
    else if (find_len(argv) == 2)
        exit(ft_atoi(argv[1]));
    return (0);
}