#include "minishell.h"

void	check_list(t_envp *list)
{
	t_envp	*tmp_lst;

	tmp_lst = list;
	while (tmp_lst)
	{
		printf("declare -x %s=\"%s\"\n", tmp_lst->key, tmp_lst->value);
		tmp_lst = tmp_lst->next;
	}
}

char	**get_arr_env(t_envp *env)
{
	t_envp	*tmp;
	char	**arr;
	char	*tmp_str;
	int		i;
	// int		j;

	tmp = env;
	i = ft_lstsize(tmp);
	// arr = malloc(i);
	arr = NULL;
	i = 0;
	while (tmp)
	{
		arr[i] = (char *)malloc(ft_strlen(tmp->key) + ft_strlen(tmp->value) + 1); // здесь поломка!
		if (!arr[i])
			printf("so bad\n");
		// printf("Not bad\n");
		tmp_str = ft_strjoin(tmp->key, "=");
		arr[i] = ft_strjoin(tmp_str, tmp->value);
		// printf("%s\n", arr[i]);
		tmp = tmp->next;
		i++;
	}
	return (arr);
}
