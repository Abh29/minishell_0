/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:13:58 by ddelena           #+#    #+#             */
/*   Updated: 2022/03/04 03:02:23 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

void	change_dir2(char *path)
{
	char	tmp[1025];
	char	*oldpwd;

	oldpwd = getcwd(tmp, 1024);
	if (chdir(path) != 0)
		ft_exit("Error : couldn't change dir !\n", 1);
	ft_setenv("OLDPWD", oldpwd);
	oldpwd = getcwd(tmp, 1024);
	ft_setenv("PWD", oldpwd);
	ft_set_envp();
}

int	ft_cd(t_cmd *cmd)
{
	char	*home;

	if (cmd->args[1] == NULL || ft_strncmp(cmd->args[1], "~", 2) == 0)
	{
		home = ft_strdup(getenv("HOME"));
		if (home == NULL)
			ft_exit("Error : couldn't find HOME \n", 1);
		change_dir2(home);
		free(home);
	}
	else
		change_dir2(cmd->args[1]);
	ft_set_envp();
	exit(0);
}
