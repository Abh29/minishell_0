#include "../libft/libft.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>

int	print_error(void)
{
    ft_putstr_fd(strerror(errno), 2);
    write(2, "\n", 2);
    return (1);
}

void ft_pwd(void)
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
        free(pwd);
        return (1);
    }
}
