/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 19:06:04 by mehill            #+#    #+#             */
/*   Updated: 2021/12/05 20:11:55 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

t_io_red	*ft_new_io_red(void)
{
	t_io_red	*out;

	out = malloc (sizeof(t_io_red));
	if (out == NULL)
		return (NULL);
	out->fdin = 0;
	out->fdout = 1;
	out->fderr = 2;
	out->limiter = NULL;
	out->append = 0;
	return (out);
}

t_cmd	*ft_new_cmd(void)
{
	t_cmd	*out;

	out = malloc(sizeof(t_cmd));
	if (out == NULL)
		return (NULL);
	out->cmd_name = NULL;
	out->args = NULL;
	out->envp = NULL;
	out->exit_stat = NULL;
	out->red = ft_new_io_red();
	out->ors = NULL;
	out->ands = NULL;
	out->pipe = NULL;
	out->ands_ors = NULL;
	out->log = 0;
	return (out);
}

void	ft_free_io_red(t_io_red **red)
{
	if (red == NULL || *red == NULL)
		return ;
	if ((*red)->limiter)
		free((*red)->limiter);
	free(*red);
	*red = NULL;
}

//TODO: free envp??
void	ft_free_cmd(t_cmd **cmd)
{
	if ((*cmd)->cmd_name)
		free((*cmd)->cmd_name);
	ft_free_split(&(*cmd)->args);
	ft_free_split(&(*cmd)->envp);
	ft_free_io_red(&(*cmd)->red);
	if ((*cmd)->ors)
		ft_free_cmd_list(&((*cmd)->ors));
	if ((*cmd)->ands)
		ft_free_cmd_list(&((*cmd)->ands));
	if ((*cmd)->pipe)
		ft_free_cmd_list(&((*cmd)->pipe));
	if ((*cmd)->ands_ors)
		ft_free_cmd_list(&((*cmd)->ands_ors));
	free(*cmd);
	*cmd = NULL;
}
