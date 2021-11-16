#include "../mch.h"

//TODO: check for builtins
t_cmd	*ft_fill_cmd(char *line, char **argv, char **envp)
{
	t_cmd		*cmd;
	char		**spt;
	char		*exp;
//	extern int	size;
//	extern char	*save;

//	printf("this is fill cmd \n<%s>", line);
//	getchar();
//	ft_printline(save, size, 1);
//	printf("\n");
//	getchar();
	cmd = ft_new_cmd();
	cmd->ands_ors = ft_get_ands_ors_list(line, argv, envp);
//	if (cmd->ands_ors)
//	{
//		printf("after get ands ors \n<%s>", line);
//		getchar();
//		ft_printline(save, size, 1);
//		printf("\n");
//		getchar();
//	}
	cmd->pipe = ft_get_pipes_list(line, argv, envp);
	exp = ft_expand_dollar(line);
	spt = ft_split_args(exp);
	cmd->cmd_name = ft_which(spt[0], envp);
	ft_get_redctn(cmd->red, spt);
	cmd->envp = ft_vectdup(argv);
	cmd->args = ft_vectdup(spt);
	ft_free_split(&spt);
	free(exp);
	return (cmd);
}
//echo cmd1 | echo cmd2 && echo cmd3 | echo cmd4 && echo cmd5 || echo cmd6 | echo cmd7