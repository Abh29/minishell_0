#include "mch.h"

t_cmd *cmd;
int size;
char *save;

t_global	g_msh;

int	execute_cmd(t_cmd *cmd)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		execv(cmd->cmd_name, cmd->args);
	return pid;
}

void	execute_cmd_list(t_dlist *cmds)
{
	int	status;

	while (cmds)
	{
		g_msh.pid_fg = ft_execute_cmd(cmds->content, g_msh.ret);
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

void	handle_sigint(int sig)
{	(void)sig; //do nothing;
	if (g_msh.pid_fg != 0)
		kill(g_msh.pid_fg, sig);
	g_msh.buff_idx = 0;
	ft_reset_input_buff();
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(SHELL_NAME, 1);
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	char	pwd[PATH_MAX];
	int		status;
	t_dlist	*lst;
	static struct termios oldt, newt;

	g_msh.argc = argc;
	g_msh.argv = argv;
	g_msh.envp = envp;
	g_msh.ret = malloc(sizeof(int));
	g_msh.buff_idx = 0;
	(void) argv;
	(void) envp;
	(void) status;
	(void) lst;
	(void) oldt;
	(void) newt;
	*pwd = 0;
	/*getcwd(pwd, sizeof(pwd));
	printf("cwd : %s\n", pwd);
	ft_bzero(pwd, sizeof(pwd));
	ttyname_r(0, pwd, sizeof(pwd));
	printf("ttyname : %s\n", pwd);
	printf("path: %s\n", getenv("PATH"));
	printf("access : %d\n", access("/usr/bin/clear", F_OK | X_OK));
	line = ft_strdup("");*/
	signal(SIGINT, handle_sigint);
	g_msh.line = NULL;
//	tcgetattr(STDIN_FILENO, &oldt);
//	newt = oldt;
//	newt.c_lflag &= ~(ICANON);
//	newt.c_lflag &= (ICANON | ISIG | IEXTEN | ECHO | ECHOE | ECHOK | ECHOKE | ECHOCTL | PENDIN | FLUSHO);
//	newt.c_lflag &= ~(ECHOPRT | ALTWERASE | NOFLSH | TOSTOP | ECHONL | NOKERNINFO | EXTPROC);
//	newt.c_cc[VMIN] = 1;
//	newt.c_cc[VTIME] = 0;
//	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	while (1)
	{
		g_msh.pid_fg = 0;
		if (g_msh.line)
			free(g_msh.line);
		//g_msh.line = ft_get_cmd_line(1);
		g_msh.line = readline("hello > ");
		printf("g_msh.line : %s\n", g_msh.buff);
		printf("g_msh.index: %d\n", g_msh.buff_idx);
		if (!g_msh.line || ft_strncmp(g_msh.line, "exit\n", 5) == 0)
			break ;
		if (*g_msh.line == '\n' || *g_msh.line == '\t')
			continue ;
		g_msh.line[ft_strlen(g_msh.line) - 1] = 0;
		size = ft_strlen(g_msh.line);
		save = g_msh.line;
		lst = ft_get_cmd_list(g_msh.line, argv, envp);
		//ft_print_cmd_list(lst, 1);
		execute_cmd_list(lst);
		while (wait(&status) > 0);
		ft_free_cmd_list(&lst);
	}
	if (g_msh.line)
		free(g_msh.line);
//	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return (0);
}
//aghonjeyale9el9 