#include "mch.h"

int	main(int argc, char **argv)
{
	char	*line;
    static struct termios oldt, newt;

	(void)argc;
	(void)argv;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	newt.c_cc[VMIN] = 1;
	newt.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	line = ft_get_shell_line();
	printf("main : %s\n", line);
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return (0);
}
