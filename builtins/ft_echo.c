#include "../libft/libft.h"

void ft_echo(int argc, char **argv)
{
    int flag;
    int i;

    flag = 0;
    i = 2;
    if (argv[i] && argc > 2)
    {
        if (!ft_strncmp("-n", argv[2], 2))
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
}
