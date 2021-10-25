#include "minishell.h"

int	wildcards_handler(t_shell *minishell, int *i)
{
	if (minishell->input[*i] == '*' && minishell->apps->is_argv == 1) // сюда можно добавить условие, при котором '*' не будет разворачиваться
		minishell->apps->token = WILDCARD_ASTERISK;
	return (0);
}