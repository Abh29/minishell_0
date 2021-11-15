#include "mch.h"

t_cmd *cmd;
int size;
char *save;

void	execute_cmd(t_cmd *cmd)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		execv(cmd->cmd_name, cmd->args);
	return ;
}

void	execute_cmd_list(t_dlist *cmds)
{
	int	status;

	while (cmds)
	{
		execute_cmd(cmds->content);
		cmds = cmds->next;
		while (wait(&status) > 0);
	}
}

void ft_list_pwd_files(void)
{
  DIR *d;
  struct dirent *dir;

  d = opendir(".");
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      printf("%s\n", dir->d_name);
    }
    closedir(d);
  }
}

int	main(int argc, char **argv, char **envp)
{
	char	pwd[PATH_MAX];
	char	*line;
	int		status;
	t_dlist	*lst;

	(void) argc;
	(void) argv;
	(void) envp;
	(void) status;
	(void) lst;
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
		size = ft_strlen(line);
		save = line;
		lst = ft_get_cmd_list(line, argv, envp);
		ft_print_cmd_list(lst, 1);
		execute_cmd_list(lst);
		while (wait(&status) > 0);
		ft_free_cmd_list(&lst);
	}
	free(line);
	return (0);
}
