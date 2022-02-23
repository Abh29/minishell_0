/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 17:16:45 by mehill            #+#    #+#             */
/*   Updated: 2022/02/23 20:12:38 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

//TODO: check for builtins
t_cmd	*ft_fill_cmd(char *line, char **argv, char **envp)
{
	t_cmd		*cmd;
	char		**spt;
	char		*exp;

	cmd = ft_new_cmd();
	cmd->ands_ors = ft_get_ands_ors_list(line, argv, envp);
	cmd->pipe = ft_get_pipes_list(line, argv, envp);
	exp = ft_expand_dollar(line);
	ft_fill_in_redirection(cmd->red, exp);
	ft_fill_out_redirection(cmd->red, exp);
	spt = ft_split_args(exp);
	ft_trim_args(spt);
	cmd->cmd_name = ft_which(spt[0], envp, &cmd->builting);
	ft_expand_args_astrix(&spt);
	cmd->envp = ft_vectdup(argv);
	cmd->args = ft_vectdup(spt);
	ft_free_split(&spt);
	free(exp);
	return (cmd);
}
