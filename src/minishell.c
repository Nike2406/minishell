#include "minishell.h"

int	minishell_parser(t_shell *minishell)
{
	int	i;

	i = 0;
	if (space_cut_begin(minishell))
		return (0);
	if (minishell->input == NULL)
		return (0);
	add_application(minishell);
	while (minishell->input)	{
		if (minishell->input[i] == '$')
			minishell->input = dollar(minishell, &i);
		else if (single_quote(minishell, &i))
			return (0);
		else if (double_quote(minishell, &i))
			return (0);
		else if (minishell->input[i] == ' ' || minishell->input[i] == '\t'
				|| minishell->input[i] == 0)
			split_into_arguments(minishell, &i);
		else if (tokens_handler(minishell, &i))
			return (0);
		else if (wildcards_handler(minishell, &i))
			return (0);
		i++;
	}

	return (1);
}

void	initialization(t_shell *minishell, int argc, char **argv)
{
	minishell->argc = argc;
	minishell->argv = argv;
	minishell->child_exit_status = 0;
	minishell->apps = NULL;
	minishell->fd0_source = dup(0);
	minishell->fd1_source = dup(1);
	minishell->fd2_source = dup(2);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell minishell;
	get_environment(envp, &minishell);
	rl_outstream = stderr;
	check_shlvl(&minishell);
	initialization(&minishell, argc, argv);
	base_signal();
	while (1)
	{
		minishell.input = readline("\e[0;32mminishell$\e[0;39m ");
		if (!(minishell.input))
			input_eof();
		if (ft_strlen(minishell.input) == 0)
		{
			free(minishell.input);
			continue;
		}
		add_history(minishell.input);
		if (minishell_parser(&minishell))
			minishell_executor(&minishell);
		garbage_collector(&minishell);
	}
}

//after to remove