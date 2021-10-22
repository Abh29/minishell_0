/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:37:14 by mehill            #+#    #+#             */
/*   Updated: 2021/10/22 22:38:37 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstnew(void *content)
{
	t_dlist	*out;

	out = malloc(sizeof(t_list));
	if (out == NULL)
		return (NULL);
	out->content = content;
	out->next = NULL;
	out->prev = NULL;
	return (out);
}
