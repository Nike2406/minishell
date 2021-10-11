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
