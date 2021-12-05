/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 20:16:53 by mehill            #+#    #+#             */
/*   Updated: 2021/12/05 20:16:54 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

char	**ft_expand_args(char **vect)
{
	char	**out;
	int		i;
	char	*p;

	i = 0;
	while (vect[i])
		i++;
	out = malloc(sizeof(char *) * (i + 1));
	if (out == NULL)
		return (NULL);
	i = 0;
	while (vect[i])
	{
		p = ft_get_next_dollar(vect[i]);
		if (p)
			out[i] = ft_expand_dollar(vect[i]);
		else
			out[i] = ft_strdup(vect[i]);
		i++;
	}
	out[i] = NULL;
	return (out);
}
