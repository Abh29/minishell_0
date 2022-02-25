/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:17:08 by ddelena           #+#    #+#             */
/*   Updated: 2022/02/26 01:01:36 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

char	**ft_lst_get_array(t_list *lst)
{
	int		size_array;
	char	**arr;

	size_array = ft_lstsize(lst) + 1;
	arr = memory_error(sizeof(*arr) * size_array);
	if (!arr)
		return (NULL);
	arr[--size_array] = NULL;
	while (lst)
	{
		arr[--size_array] = ft_strdup(lst->content);
		lst = lst->next;
	}
	return (arr);
}

void	*memory_error(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_putendl_fd("Critical error: cannot allocate memory", 2);
		exit(errno);
	}
	return (ptr);
}
