#include "../mch.h"

char	**ft_expand_args(char **vect)
{
	char	**out;
	int		i;
	char	*p;

	i = 0;
	while (vect[i])
		i++;
	out = malloc(sizeof(char *) * (i + 1));
	if (out == NULL)
		return (NULL);
	i = 0;
	while (vect[i])
	{
		p = ft_get_next_dollar(vect[i]);
		if (p)
			out[i] = ft_expand_dollar(vect[i]);
		else
			out[i] = ft_strdup(vect[i]);
		i++;
	}
	out[i] = NULL;
	return (out);
}
