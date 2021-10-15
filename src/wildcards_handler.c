#include "minishell.h"

int	wildcards_handler(t_shell *minishell, int *i)
{
	if (minishell->input[*i] == '*')
		minishell->apps->token = WILDCARD_ASTERISK;
	return (0);
}