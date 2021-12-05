/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 17:18:40 by mehill            #+#    #+#             */
/*   Updated: 2021/12/05 17:34:42 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

void	ft_trim_args(char **args)
{
	char	*tmp;
	int		i;

	if (args == NULL)
		return ;
	i = 0;
	while (args[i])
	{
		if (args[i][0] == '\'' || args[i][0] == '\"')
		{
			tmp = ft_substr(args[i], 1, ft_strlen(args[i]) - 2);
			free(args[i]);
			args[i] = tmp;
		}
		i++;
	}
}
