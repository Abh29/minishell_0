/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_which.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 23:19:04 by mehill            #+#    #+#             */
/*   Updated: 2022/03/05 20:05:08 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mch.h"

//TODO: add builtings !!

void	ft_check_builtings(char *cmd, t_builtings *builting)
{
	if (!cmd)
		return ;
	*builting = FT_NULL;
	if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		*builting = FT_ENV;
	else if (!ft_strncmp(cmd, "history", ft_strlen(cmd)))
		*builting = FT_HISTORY;
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		*builting = FT_UNSET;
	else if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		*builting = FT_ECHO;
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		*builting = FT_CD;
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		*builting = FT_EXIT;
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		*builting = FT_PWD;
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		*builting = FT_EXPORT;
	else if (*cmd == '(' && cmd[ft_strlen(cmd) - 1] == ')' && \
	ft_strlen(cmd) > 2)
		*builting = FT_SUBSHELL;
}

static char	*ft_check_possible(char	**paths, char *scmd)
{
	char	*pcmd;

	if (paths == NULL || *paths == NULL)
		return (NULL);
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

char	*ft_which(char	*cmd, t_builtings *builting)
{
	char	**paths;
	char	*scmd;
	char	*pcmd;
	char	*path;

	if (!cmd)
		return (NULL);
	ft_check_builtings(cmd, builting);
	scmd = ft_strjoin("/", cmd);
	path = ft_getenv("PATH");
	paths = ft_split(path, ':');
	pcmd = ft_check_possible(paths, scmd);
	ft_free_split(&paths);
	if (scmd)
		free(scmd);
	if (path)
		free(path);
	scmd = NULL;
	if (pcmd == NULL)
		return (ft_strdup(cmd));
	return (pcmd);
}
