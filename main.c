#include "mch.h"

int	main(int argc, char **argv, char **envp)
{
	char	pwd[PATH_MAX];
	char	*line;

	(void) argc;
	(void) argv;
	*pwd = 0;
	getcwd(pwd, sizeof(pwd));
	printf("cwd : %s\n", pwd);
	ft_bzero(pwd, sizeof(pwd));
	ttyname_r(0, pwd, sizeof(pwd));
	printf("ttyname : %s\n", pwd);
	printf("path: %s\n", getenv("PATH"));
	printf("access : %d\n", access("/usr/bin/clear", F_OK | X_OK));
	while (1)
	{
		ft_putstr_fd(SHELL_NAME, 1);
		line = get_next_line(1);
		if (*line == '\n' || *line == '\t')
			continue ;
		if (ft_strncmp(line, "exit\n", 5) == 0)
			break ;
		if (line)
			line[ft_strlen(line) - 1] = 0;
		printf("%s\n", ft_which(line, envp));
		free(line);
	}
	return (0);
}
