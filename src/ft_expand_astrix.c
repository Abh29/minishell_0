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
	return (NULL);
}

void	ft_expand_args_astrix(char ***args)
{
	t_dlist	*lst_args;

	printf("here !");
	getchar();
	lst_args = ft_expanded_args_astrix_list(*args);
	if (lst_args == NULL)
		return ;
	printf("here !");
	while (lst_args)
	{
		printf("args: %s\n", (char *)lst_args->content);
		lst_args = lst_args->next;
	}
	getchar();
	ft_free_split(args);
	printf("here !");
	getchar();
	*args = ft_lst_to_arr(lst_args);
	printf("here ! %p\n", *args);
	ft_print_splt(*args, 1);
	getchar();
}
