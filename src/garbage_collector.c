#include "minishell.h"

void	garbage_collector(t_shell *minishell)
{
	t_prog	*tmp;
	int		i;

	if (minishell->apps != NULL)
		minishell->apps = minishell->apps->head;
	while (minishell->apps != NULL)
	{
		i = 0;
		while (minishell->apps->argv && minishell->apps->argv[i])
			free(minishell->apps->argv[i++]);
		free(minishell->apps->argv);
		if (minishell->apps->output_file != NULL)
			free(minishell->apps->output_file);
		if (minishell->apps->input_file != NULL)
			free(minishell->apps->input_file);
		tmp = minishell->apps;
		minishell->apps = minishell->apps->next;
		free(tmp);
	}
	if (minishell->input != NULL)
		free(minishell->input);
}