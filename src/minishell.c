/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 00:05:22 by prochell          #+#    #+#             */
/*   Updated: 2021/09/07 20:02:02 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (minishell->input[i] == '\'')
			minishell->input = single_quote(minishell->input, &i);
		else if (minishell->input[i] == '\"')
		{
			minishell->input = double_quote(minishell, &i);
//			printf("%s\n", minishell->input + i);
		}
	}
		// Prochell
		// Start
		char	**tmp; // временный массив для проверки builtins

		tmp = ft_split(minishell->input, ' '); // подача двойного массива
		if (get_pwd(minishell, tmp) < 1)
			return ;
		else if (get_echo(tmp) < 1)
			return ;
		else if (get_cd(minishell, tmp) < 1)
			return ;
		// End
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
	t_shell	minishell;

	// Добавил парсер окружения
	// Start
	get_envp(envp, &minishell);

	// // Check env
	// t_envp	*env_tmp;
	// env_tmp = minishell.environment;
	// while (env_tmp != NULL)
	// {
	// 	printf("key = %s, value = %s\n", env_tmp->key, env_tmp->value);
	// 	env_tmp = env_tmp->next;
	// }
	// End

	initialization(&minishell, argc, argv, envp);
	while (1)
	{
		minishell.input = readline("minishell$ ");
		if (!(minishell.input))
			input_eof();
		if (ft_strlen(minishell.input) == 0)
			continue;
			// printf("нужно удалить историю, если нулевая длина");
		// if (minishell.input == "\n")
		// 	printf("lol");
		add_history(minishell.input);
		parser(&minishell);


	}
}
