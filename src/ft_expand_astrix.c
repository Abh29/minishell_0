#include "../mch.h"

t_dlist	*ft_expanded_args_astrix_list(char **args)
{
	int		i;
	t_dlist	*matches;
	t_dlist	*out;

	if (args == NULL || *args == NULL)
		return (NULL);
	out = NULL;
	ft_dlstadd_back(&out, ft_dlstnew(ft_strdup(args[0])));
	i = 1;
	while (args[i])
	{
		matches = ft_get_astrix_matches(args[i]);
		if (matches == NULL)
			ft_dlstadd_back(&out, ft_dlstnew(ft_strdup(args[i])));
		else
		{
			ft_dlstadd_back(&out, matches);
		}
		i++;
	}
	return (out);
}

char	**ft_lst_to_arr(t_dlist *args)
{
	char	**out;
	int		i;

	if (args == NULL)
		return (NULL);
	out = malloc ((ft_dlstsize(args) + 1) * sizeof(char *));
	if (out == NULL)
		ft_exit("Error : could not allocate memory for expanded args !", 1);
	i = 0;
	while (args)
	{
		out[i++] = (char *)args->content;
		args = args->next;
	}
	out[i] = NULL;
	return (out);
}

// TODO: free lst_args ?
void	ft_expand_args_astrix(char ***args)
{
	t_dlist	*lst_args;
	t_dlist	*p;

	lst_args = ft_expanded_args_astrix_list(*args);
	if (lst_args == NULL)
		return ;
	ft_free_split(args);
	*args = ft_lst_to_arr(lst_args);
	while (lst_args)
	{
		p = lst_args->next;
		free(lst_args);
		lst_args = p;
	}
}
