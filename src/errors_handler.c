#include "minishell.h"

int	syntax_error(t_shell *minishell, const char symbol)
{
	write(2, "minishell: ", 11);
	if (symbol == 0)
		write(2, "syntax error: unexpected end of file\n", 37);
	else
	{
		write(2, "syntax error near unexpected token '", 36);
		write(2, &symbol, 1);
		write(2, "'\n", 2);
	}
	minishell->child_exit_status = 258;
	return (1);
}

int	standard_error(t_shell *minishell, char *arg_name)
{
	write(2, "minishell: ", 11);
	perror(arg_name);
	minishell->child_exit_status = 1;
	return (1);
}