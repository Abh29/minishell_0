/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:13:56 by ddelena           #+#    #+#             */
/*   Updated: 2022/02/26 01:01:46 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

int ft_echo(int argc, char **argv)
{
    int flag;
    int i;

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