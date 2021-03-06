/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:32:45 by mehill            #+#    #+#             */
/*   Updated: 2021/10/15 19:19:10 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

static void	ft_firstcheck(const char **str, int *sign)
{
	while (**str && ft_isspace(**str))
		(*str)++;
	if (**str == '-')
	{
		(*str)++;
		*sign = -1;
	}
	else if (**str == '+')
		(*str)++;
}

int	ft_atoi(const char *str)
{
	int					sign;
	unsigned long long	out;

	sign = 1;
	out = 0;
	ft_firstcheck(&str, &sign);
	while (*str && ft_isdigit(*str))
	{
		out = out * 10 + *str - 48;
		str++;
		if (out > 9223372036854775806L)
		{
			if (sign == 1)
				return (-1);
			if (out > 9223372036854775807L)
				return (0);
			return (1);
		}
	}
	return ((int)(out * sign));
}
