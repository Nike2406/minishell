#include "minishell.h"

void	input_eof(void)
{
	printf("\b\bexit\n"); // костыль?
	exit(0);
}

void	minishell_parser(t_shell *minishell)
{
	int	i;

	i = 0;
	minishell->apps = (t_prog *)malloc(sizeof(t_prog));
	minishell->apps->argc = 0;
	minishell->apps->argv = NULL;
	minishell->apps->next = NULL;
	
	if (minishell->input[i] == ' ' || minishell->input[i] == '\t')
			minishell->input = space_cut_begin(minishell);
	while (minishell->input)
	{
		if (minishell->input[i] == '$')
			minishell->input = dollar(minishell, &i);
		else if (minishell->input[i] == '\'')
			minishell->input = single_quote(minishell, &i);
		else if (minishell->input[i] == '\"')
			minishell->input = double_quote(minishell, &i);
		else if (minishell->input[i] == ' ' || minishell->input[i] == '\t'
				|| minishell->input[i] == 0)
			minishell->input = space_cut(minishell, &i);
		i++;
	}
	// printf("%s\n", minishell->input);
}

void	initialization(t_shell *minishell, int argc, char **argv, char **envp)
{
		/*
	Стартовая и разовая инициализация всякого мусора запихать в одну функцию,
	например, сигналы:
	signal(SIGINT, sighandler);
	*/
	minishell->argc = argc;
	minishell->argv = argv;
	minishell->envp = envp;
	minishell->child_exit_status = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell minishell;


	initialization(&minishell, argc, argv, envp);
	while (1)
	{
		minishell.input = readline("minishell$ ");
		if (!(minishell.input))
			input_eof();
		if (ft_strlen(minishell.input) == 0)
		{
			free(minishell.input);
			continue;
		}
		add_history(minishell.input);
		minishell_parser(&minishell);
		minishell_executor(&minishell);
		garbage_collector(&minishell);
	}
}
