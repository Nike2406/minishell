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

	tmp = env;
	i = ft_lstsize(tmp);
	arr = malloc(i);
	i = 0;
	while (tmp)
	{
		arr[i] = (char *)malloc(ft_strlen(tmp->key) + ft_strlen(tmp->value) + 2); // здесь поломка!
		tmp_str = ft_strjoin(tmp->key, "=");
		tmp_str = ft_strjoin(tmp_str, tmp->value);
		//============================== !  Тут дополнительный перенос !===============================
		arr[i] = ft_strjoin(tmp_str, "\n");
		tmp = tmp->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
