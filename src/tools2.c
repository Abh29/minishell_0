/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 23:24:19 by mehill            #+#    #+#             */
/*   Updated: 2021/10/25 19:54:42 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

void	ft_free_split(char ***split)
{
	void	*p;

	p = (char **)*split;
	if (split == NULL || *split == NULL)
		return ;
	while (**split != NULL)
	{
		free(**split);
		**split = NULL;
		(*split)++;
	}
	*split = NULL;
	free(p);
	p = NULL;
}

void	ft_free_args(char ***split, int n)
{
	void	*p;

	p = (char **)*split;
	if (split == NULL || *split == NULL || n < 0)
		return ;
	while (n--)
	{
		free(**split);
		**split = NULL;
		(*split)++;
	}
	*split = NULL;
	free(p);
	p = NULL;
}

char	**ft_vectdup(char **vect)
{
	char	**out;
	int		i;

	i = 0;
	while (vect[i])
		i++;
	out = malloc(sizeof(char *) * (i + 1));
	if (out == NULL)
		return (NULL);
	i = 0;
	while (vect[i])
	{
		out[i] = ft_strdup(vect[i]);
		i++;
	}
	out[i] = NULL;
	return (out);
}
