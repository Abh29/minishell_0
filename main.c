#include "mch.h"

void	execute_cmd(t_cmd *cmd)
{
	int pid = fork();

	if (pid == 0)
		execv(cmd->cmd_name, cmd->args);
	return ;
}

t_cmd	*ft_fill_cmd(char *line, char **argv, char **envp)
{
	t_cmd	*cmd;
	char	**spt;

	spt = ft_split(line, ' ');
	cmd = ft_new_cmd();
	cmd->cmd_name = ft_which(spt[0], envp);
	cmd->envp = ft_vectdup(argv);
	cmd->args = ft_vectdup(spt);
	cmd->red = ft_new_io_red();
//	printf("spt : %p\ncmd : %p\ncmd_name : %p\nenvp : %p\nargs : %p\nio : %p\n",spt, cmd, cmd->cmd_name, cmd->args, cmd->envp, cmd->red);
	ft_free_split(&spt);
	return (cmd);
}

int	main(int argc, char **argv, char **envp)
{
	char	pwd[PATH_MAX];
	char	*line;
	t_cmd	*cmd;
	int		status;

	(void) argc;
	(void) argv;
	(void) envp;
	*pwd = 0;
	getcwd(pwd, sizeof(pwd));
	printf("cwd : %s\n", pwd);
	ft_bzero(pwd, sizeof(pwd));
	ttyname_r(0, pwd, sizeof(pwd));
	printf("ttyname : %s\n", pwd);
	printf("path: %s\n", getenv("PATH"));
	printf("access : %d\n", access("/usr/bin/clear", F_OK | X_OK));
	line = ft_strdup("");
	while (1)
	{
		if (line)
			free(line);
		ft_putstr_fd(SHELL_NAME, 1);
		line = get_next_line(1);
		if (*line == '\n' || *line == '\t')
			continue ;
		if (ft_strncmp(line, "exit\n", 5) == 0)
			break ;
		if (line)
			line[ft_strlen(line) - 1] = 0;
		cmd = ft_fill_cmd(line, argv, envp);
		execute_cmd(cmd);
		while (wait(&status) > 0);
		ft_free_cmd(&cmd);
		free(cmd);
	}
	free(line);
	return (0);
}
