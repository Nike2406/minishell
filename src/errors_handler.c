#include "minishell.h"

int	syntax_error(t_shell *minishell, const char *token, int len)
{
	write(2, "minishell: ", 11);
	if (token[0] == 0)
		write(2, "syntax error near unexpected token `newline'\n", 45);
	else
	{
		write(2, "syntax error near unexpected token `", 36);
		write(2, token, len);
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
	minishell->apps->do_not_launch = 1;
	return (1);
}

int	executing_error(t_shell *minishell)
{
	write(2, "minishell: ", 11);
	write(2, minishell->apps->argv[0], ft_strlen(minishell->apps->argv[0]));
	write(2, ": command not found\n", 20);
	// minishell->child_exit_status = 127;
	return (1);
}
