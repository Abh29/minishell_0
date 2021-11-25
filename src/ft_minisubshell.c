#include "../mch.h"

//TODO: add lexer chekings !!!
int	ft_mini_sub_shell(char *line, char **argv, char **envp)
{
	int		status;
	t_dlist	*lst;

	if (line == NULL)
		return (1);
	if (line[0] == '(' && line[ft_strlen(line) - 1] == ')')
	{
		line[ft_strlen(line) - 1] = 0;
		line++;
	}
	if (ft_strncmp(line, "exit\n", 5) == 0)
			return (0);
	lst = ft_get_cmd_list(line, argv, envp);
	execute_cmd_list(lst);
	while (wait(&status) > 0);
	ft_free_cmd_list(&lst);
	return (0);
}
