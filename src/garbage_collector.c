#include "minishell.h"

void	garbage_collector(t_shell *minishell)
{
	t_prog	*tmp;
	int		i;

	while (minishell->apps != NULL) // если будут токены, то добавить им фри
	{
		i = 0;
		while (minishell->apps->argv[i])
			free(minishell->apps->argv[i++]);
		free(minishell->apps->argv);
		tmp = minishell->apps;
		minishell->apps = minishell->apps->next;
		free(tmp);
	}
}