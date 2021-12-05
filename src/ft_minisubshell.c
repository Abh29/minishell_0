/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minisubshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 20:29:48 by mehill            #+#    #+#             */
/*   Updated: 2021/12/05 20:30:39 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

//TODO: add lexer chekings !!!
int	ft_mini_sub_shell(char *line, char **argv, char **envp)
{
	int		status;
	t_dlist	*lst;

	if (line == NULL)
		return (1);
	if (line[0] == '(' && line[ft_strlen(line) - 1] == ')')
	{
		line[ft_strlen(line) - 1] = 0;
		line++;
	}
	if (ft_strncmp(line, "exit\n", 5) == 0)
		return (0);
	lst = ft_get_cmd_list(line, argv, envp);
	execute_cmd_list(lst);
	while (wait(NULL) > 0)
		(void)status;
	ft_free_cmd_list(&lst);
	return (0);
}
