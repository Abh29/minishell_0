/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minisubshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 20:29:48 by mehill            #+#    #+#             */
/*   Updated: 2022/02/23 22:04:46 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

//TODO: add lexer chekings !!!
void	ft_subshell(t_cmd *cmd)
{
	extern t_global	g_msh;
	int				status;
	t_dlist			*lst;
	int				err;
	int				pos;

	if (cmd == NULL)
		exit(1);
	if (cmd->cmd_name[0] == '(')
		cmd->cmd_name++;
	if (cmd->cmd_name[ft_strlen(cmd->cmd_name) - 1] == ')')
		cmd->cmd_name[ft_strlen(cmd->cmd_name) - 1] = 0;
	ft_check_cmd_line(cmd->cmd_name, &err, &pos);
	if (err != 0)
		exit (err);
	lst = ft_get_cmd_list(cmd->cmd_name, g_msh.argv, g_msh.envp);
	execute_cmd_list(lst);
	while (wait(&status) > 0)
		(void) status;
	ft_free_cmd_list(&lst);
	exit(WEXITSTATUS(status));
}
