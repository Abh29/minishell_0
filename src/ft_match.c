/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 20:29:26 by mehill            #+#    #+#             */
/*   Updated: 2021/12/05 20:29:34 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

int	ft_match_astrix(char *pattern, char *str)
{
	char	**spt;
	char	*p;
	char	*save;
	int		i;
	int		j;

	save = str;
	spt = NULL;
	while (*pattern && *pattern != '*' && *str)
	{
		if (*str != *pattern)
			return (0);
		str++;
		pattern++;
	}
	spt = ft_split(pattern, '*');
	i = 0;
	while (spt[i])
	{
		p = ft_strnstr(str, spt[i], ft_strlen(str));
		if (p == NULL)
			return (0);
		str = p + ft_strlen(spt[i]);
		i++;
	}
	if (spt)
		ft_free_split(&spt);
	i = ft_strlen(pattern) - 1;
	j = ft_strlen(save) - 1;
	while (i >= 0 && j >= 0 && pattern[i] != '*' && pattern[i] == save[j])
	{
		i--;
		j--;
	}
	if (pattern[i] != '*' && i != j)
		return (0);
	return (1);
}
