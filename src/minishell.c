#include "minishell.h"

void	input_eof(void)
{
	printf("\b\bexit\n"); // костыль?
	exit(0);
}

void	parser(t_shell *minishell)
{
	int	i;

	i = -1;
	while (minishell->input[++i])
	{
		if (minishell->input[i] == '$')
			minishell->input = dollar(minishell, &i);
		else if (minishell->input[i] == '\'')
			minishell->input = single_quote(minishell->input, &i);
		else if (minishell->input[i] == '\"')
			minishell->input = double_quote(minishell, &i);
		
	}
		printf("%s\n", minishell->input);
	free(minishell->input);
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
			continue;
		// if (minishell.input == "\n")
		// 	printf("lol");
		add_history(minishell.input);
		parser(&minishell);

		
	}
}
