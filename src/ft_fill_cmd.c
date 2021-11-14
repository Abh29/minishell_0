#include "../mch.h"

//TODO: check for builtins 
t_cmd	*ft_fill_cmd(char *line, char **argv, char **envp)
{
	t_cmd	*cmd;
	char	**spt;
	char	**espt;

	spt = ft_split_args(line);
	cmd = ft_new_cmd();
	cmd->cmd_name = ft_which(spt[0], envp);
	espt = ft_expand_args(spt);
	ft_get_redctn(cmd->red, espt);
	cmd->envp = ft_vectdup(argv);
	cmd->args = ft_vectdup(espt);
	cmd->pipe = ft_get_pipes_list(line, argv, envp);
	ft_free_split(&spt);
	ft_free_split(&espt);
	return (cmd);
}
