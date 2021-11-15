#include "../mch.h"

// FIXME: free split !
int	ft_match_astrix(char *pattern, char *str)
{
	char	**spt;
	char	*p;

	while (*pattern && *pattern != '*' && *str)
	{
		if (*str != *pattern)
			return (0);
		str++;
		pattern++;
	}
	spt = ft_split(pattern, '*');
	while (*spt)
	{
		p = ft_strnstr(str, *spt, ft_strlen(str));
		if (p == NULL)
			return (0);
		str = p + ft_strlen(*spt);
		spt++;
	}
//	ft_free_split(&spt);
	printf("rest of str |%s|\n", str);
	if (pattern[ft_strlen(pattern) - 1] != '*' && *str)
		return (0);
	return (1);
}

/*
int main(int argc, char **argv)
{
	if (argc < 3)
		return 1;
	printf("%s , %s , %d \n", argv[1], argv[2], ft_match_astrix(argv[1], argv[2]));
	return 0;
}*/
