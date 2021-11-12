#include "../mch.h"

char	*ft_next_astrix(char *str)
{
	int	q;

	q = 0;
	if (*str == '*')
		return (str);
	str++;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			if (q == 0)
				q = *str;
			else if (q == *str)
				q = 0;
		}
		else if (q == 0 && *str == '*' && *(str - 1) != '\\')
			return (str);
		str++;
	}
	return (NULL);
}
