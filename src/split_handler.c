#include "minishell.h"

char	*space_cut_begin(t_shell *minishell)
{
	char	*ret;
	int		i;

	ret = NULL;
	i = 0;
	while (minishell->input[i] == ' ' || minishell->input[i] == '\t')
	{
		i++;
	}
	if (minishell->input[i] != 0)
		ret = ft_strdup(minishell->input + i);
	free(minishell->input);
	return (ret);
}

// Expanding argv and adding new element in its end.
char	**expand_argv(t_shell *minishell, int *i)
{
	int			k;
	char		**tmp;

	k = 0;
	tmp = (char **)malloc(sizeof(char *) * (++(minishell->apps->argc) + 1));
	while (k < minishell->apps->argc - 1)
	{
		tmp[k] = minishell->apps->argv[k];
		k++;
	}
	if (minishell->apps->argv != NULL)
		free(minishell->apps->argv);
	tmp[k] = ft_substr(minishell->input, 0, *i);
	tmp[k + 1] = NULL;
	return (tmp);
}

static int	split_into_output_file(t_shell *minishell, int *i)
{
	if (minishell->apps->output_file != NULL)
	{
		if (close(minishell->apps->fd_output_file) == -1)
			return (standard_error(minishell, NULL));
		free(minishell->apps->output_file);
	}
	minishell->apps->output_file = ft_substr(minishell->input, 0, *i);
	if (minishell->apps->output_file == NULL)
		return (standard_error(minishell, NULL));
	if (minishell->apps->token == TOKEN_REDIRECT_OUTPUT)
		minishell->apps->fd_output_file = open(minishell->apps->output_file, O_WRONLY | O_CREAT, 0644);
	else
		minishell->apps->fd_output_file = open(minishell->apps->output_file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (minishell->apps->fd_input_file == -1)
		return (standard_error(minishell, minishell->apps->input_file));
	minishell->apps->token = 0;
	return (0);
}

static int	split_into_input_file(t_shell *minishell, int *i)
{
	if (minishell->apps->input_file != NULL)
	{
		if (close(minishell->apps->fd_input_file) == -1)
			return (standard_error(minishell, NULL));
		free(minishell->apps->input_file);
	}
	minishell->apps->input_file = ft_substr(minishell->input, 0, *i);
	if (minishell->apps->input_file == NULL)
		return (standard_error(minishell, NULL));
	minishell->apps->fd_input_file = open(minishell->apps->input_file, O_RDONLY, 0644);
	if (minishell->apps->fd_input_file == -1)
		return (standard_error(minishell, minishell->apps->input_file));
	minishell->apps->token = 0;
	return (0);
}

char	*split_into_arguments(t_shell *minishell, int *i) // переработать на возврат 0 или 1
{
	char	*ret;

	ret = NULL;
	if (minishell->apps->token == TOKEN_REDIRECT_OUTPUT
		|| minishell->apps->token == TOKEN_REDIRECT_OUTPUT_APPEND)
		split_into_output_file(minishell, i);
	else if (minishell->apps->token == TOKEN_REDIRECT_INPUT)
		split_into_input_file(minishell, i);
	else
		minishell->apps->argv = expand_argv(minishell, i);
	while (minishell->input[*i + 1] == ' ' || minishell->input[*i + 1] == '\t')
		++(*i);
	if (minishell->input[*i] != 0 && minishell->input[*i + 1] != 0)
		ret = ft_strdup(minishell->input + *i + 1);
	(*i) = -1;
	free(minishell->input);
	minishell->apps->is_argv = 1;

	// int check = 0;
	// printf("argc=%d\n", minishell->apps->argc);
	// while (check < minishell->apps->argc)
	// {
	// 	printf("argv[%d]=[%s]\n", check, minishell->apps->argv[check]);
	// 	check++;
	// }
	// printf("argv[%d]=[%s]\n", check, minishell->apps->argv[check]);
	// printf("ret = [%s]\n", ret);

	return (ret);
}