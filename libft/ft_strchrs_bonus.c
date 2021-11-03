#include "libft.h"

char	*ft_strchrs(char *str, char *set)
{
	if (str == NULL || set == NULL)
		return (NULL);
	while (*str)
	{
		if (ft_strchr(set, *str))
			return (str);
		str++;
	}
	return (NULL);
}
