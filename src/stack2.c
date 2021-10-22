/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 00:03:54 by mehill            #+#    #+#             */
/*   Updated: 2021/10/23 00:07:33 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

int	ft_find(t_stack *s, int elm)
{
	int	i;

	if (ft_isempty(s))
		return (-1);
	i = s->head;
	while (i != s->tail && s->arr[i] != elm)
		i = (i + 1) % MAX_SIZE;
	if (s->arr[i] == elm)
		return (i);
	return (-1);
}

void	ft_pushbottom(t_stack *s, int elm)
{
	if (ft_isfull(s))
		return ;
	s->head = (s->head + MAX_SIZE - 1) % MAX_SIZE;
	s->arr[s->head] = elm;
	s->size++;
}

int	ft_popbottom(t_stack *s)
{
	int	out;

	if (ft_isempty(s))
		return (-1);
	out = s->arr[s->head];
	s->head = (s->head + 1) % MAX_SIZE;
	s->size--;
	return (out);
}

int	ft_getindex(t_stack a, int index)
{
	int	i;

	if (index < 0 || index >= a.size)
		return (-1);
	i = a.tail - index - 1;
	if (i < 0)
		i += MAX_SIZE;
	return (a.arr[i]);
}
