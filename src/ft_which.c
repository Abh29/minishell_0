/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_which.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 23:19:04 by mehill            #+#    #+#             */
/*   Updated: 2022/02/22 19:50:48 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

//TODO: add builtings !!
static char	*ft_check_possible(char	**paths, char *scmd)
{
	char	*pcmd;

	pcmd = NULL;
	while (*paths)
	{
		pcmd = ft_strjoin(*(paths++), scmd);
		if (access(pcmd, F_OK | X_OK) == 0)
			break ;
		free(pcmd);
		pcmd = NULL;
	}
	return (pcmd);
}

char	*ft_which(char	*cmd, char **envp)
{
	char	**paths;
	char	*scmd;
	char	*pcmd;

	if (!cmd || !envp || !(*envp))
		return (NULL);
	// builtings
	scmd = ft_strjoin("/", cmd);
	paths = ft_split(getenv("PATH"), ':');
	pcmd = ft_check_possible(paths, scmd);
	ft_free_split(&paths);
	free(scmd);
	scmd = NULL;
	if (pcmd == NULL)
		return (ft_strdup(cmd));
	// check for access
	return (pcmd);
}
