#include "minishell.h"

static int	handle_pipe(t_shell *minishell, int *i);
static int	handle_or(t_shell *minishell, int *i);
static int	redirect_output(t_shell *minishell, int *i);
static int	redirect_output_append(t_shell *minishell, int *i);
static int	redirect_input(t_shell *minishell, int *i);
static int	heredoc(t_shell *minishell, int *i);
static int	single_ampersand(t_shell *minishell, int *i);
static int	double_ampersand(t_shell *minishell, int *i);

int	tokens_handler(t_shell *minishell, int *i)
{
	if (minishell->input[*i] == '|')
	{
		if (minishell->input[*i + 1] == '|')
			return (handle_or(minishell, i));
		return (handle_pipe(minishell, i));
	}
	else if (minishell->input[*i] == '>')
	{
		if (minishell->input[*i + 1] == '>')
			return (redirect_output_append(minishell, i));
		return (redirect_output(minishell, i));
	}
	else if (minishell->input[*i] == '<')
	{
		if (minishell->input[*i + 1] == '<')
			return (heredoc(minishell, i));
		return (redirect_input(minishell, i));
	}
	else if (minishell->input[*i] == '&')
	{
		if (minishell->input[*i + 1] == '&')
			return (double_ampersand(minishell, i));
		return (single_ampersand(minishell, i));
	}
	return (0);
}

static int	handle_pipe(t_shell *minishell, int *i)
{
	char	*ret;

	ret = NULL;
	if (*i != 0)
		minishell->apps->argv = expand_argv(minishell, i);
	minishell->apps->token = TOKEN_PIPE;
	add_application(minishell);
	while (minishell->input[*i + 1] == ' ' || minishell->input[*i + 1] == '\t')
		++(*i);
	if (minishell->input[*i + 1] == 0 || minishell->input[*i + 1] == '|' ||
		minishell->input[*i + 1] == '<' || minishell->input[*i + 1] == '>' ||
		minishell->input[*i + 1] == '&')
		return (syntax_error(minishell, minishell->input[*i + 1]));
	if (minishell->input[*i] != 0 && minishell->input[*i + 1] != 0)
		ret = ft_strdup(minishell->input + *i + 1);
	(*i) = -1;
	free(minishell->input);
	minishell->input = ret;

	// int check = 0;
	// printf("argc=%d, token=%d\n", minishell->apps->argc, minishell->apps->token);
	// while (check < minishell->apps->argc)
	// {
	// 	printf("argv[%d]=[%s]\n", check, minishell->apps->argv[check]);
	// 	check++;
	// }
	// printf("argv[%d]=[%s]\n", check, minishell->apps->argv[check]);
	// printf("ret = [%s]\n", ret);
	return (0);
}

static int	handle_or(t_shell *minishell, int *i)
{
	char	*ret;

	ret = NULL;
	if (*i != 0)
		minishell->apps->argv = expand_argv(minishell, i);
	++(*i);
	minishell->apps->token = TOKEN_OR;
	add_application(minishell);
	while (minishell->input[*i + 1] == ' ' || minishell->input[*i + 1] == '\t')
		++(*i);
	if (minishell->input[*i + 1] == 0 || minishell->input[*i + 1] == '|' ||
		minishell->input[*i + 1] == '<' || minishell->input[*i + 1] == '>' ||
		minishell->input[*i + 1] == '&')
		return (syntax_error(minishell, minishell->input[*i + 1]));
	if (minishell->input[*i] != 0 && minishell->input[*i + 1] != 0)
		ret = ft_strdup(minishell->input + *i + 1);
	(*i) = -1;
	free(minishell->input);
	minishell->input = ret;
	return (0);
}

static int	redirect_output(t_shell *minishell, int *i)
{
	char	*ret;

	ret = NULL;
	if (*i != 0)
		minishell->apps->argv = expand_argv(minishell, i);
	minishell->apps->token = TOKEN_REDIRECT_OUTPUT;
	while (minishell->input[*i + 1] == ' ' || minishell->input[*i + 1] == '\t')
		++(*i);
	if (minishell->input[*i + 1] == 0 || minishell->input[*i + 1] == '|' ||
		minishell->input[*i + 1] == '<' || minishell->input[*i + 1] == '>' ||
		minishell->input[*i + 1] == '&')
		return (syntax_error(minishell, minishell->input[*i + 1]));
	if (minishell->input[*i] != 0 && minishell->input[*i + 1] != 0)
		ret = ft_strdup(minishell->input + *i + 1);
	(*i) = -1;
	free(minishell->input);
	minishell->input = ret;
	return (0);
}

static int	redirect_output_append(t_shell *minishell, int *i)
{
	char	*ret;

	ret = NULL;
	if (*i != 0)
		minishell->apps->argv = expand_argv(minishell, i);
	minishell->apps->token = TOKEN_REDIRECT_OUTPUT_APPEND;
	++(*i);
	while (minishell->input[*i + 1] == ' ' || minishell->input[*i + 1] == '\t')
		++(*i);
	if (minishell->input[*i + 1] == 0 || minishell->input[*i + 1] == '|' ||
		minishell->input[*i + 1] == '<' || minishell->input[*i + 1] == '>' ||
		minishell->input[*i + 1] == '&')
		return (syntax_error(minishell, minishell->input[*i + 1]));
	if (minishell->input[*i] != 0 && minishell->input[*i + 1] != 0)
		ret = ft_strdup(minishell->input + *i + 1);
	(*i) = -1;
	free(minishell->input);
	minishell->input = ret;
	return (0);
}

static int	redirect_input(t_shell *minishell, int *i)
{
	char	*ret;

	ret = NULL;
	if (*i != 0)
		minishell->apps->argv = expand_argv(minishell, i);
	minishell->apps->token = TOKEN_REDIRECT_INPUT;
	++(*i);
	while (minishell->input[*i + 1] == ' ' || minishell->input[*i + 1] == '\t')
		++(*i);
	if (minishell->input[*i + 1] == 0 || minishell->input[*i + 1] == '|' ||
		minishell->input[*i + 1] == '<' || minishell->input[*i + 1] == '>' ||
		minishell->input[*i + 1] == '&')
		return (syntax_error(minishell, minishell->input[*i + 1]));
	if (minishell->input[*i] != 0 && minishell->input[*i + 1] != 0)
		ret = ft_strdup(minishell->input + *i + 1);
	(*i) = -1;
	free(minishell->input);
	minishell->input = ret;
	return (0);
}

static int	heredoc(t_shell *minishell, int *i) // сделать через readline
{
	char	*ret;

	ret = NULL;
	if (*i != 0)
		minishell->apps->argv = expand_argv(minishell, i);
	minishell->apps->token = TOKEN_REDIRECT_INPUT;
	++(*i);
	while (minishell->input[*i + 1] == ' ' || minishell->input[*i + 1] == '\t')
		++(*i);
	if (minishell->input[*i + 1] == 0 || minishell->input[*i + 1] == '|' ||
		minishell->input[*i + 1] == '<' || minishell->input[*i + 1] == '>' ||
		minishell->input[*i + 1] == '&')
		return (syntax_error(minishell, minishell->input[*i + 1]));
	if (minishell->input[*i] != 0 && minishell->input[*i + 1] != 0)
		ret = ft_strdup(minishell->input + *i + 1);
	(*i) = -1;
	free(minishell->input);
	minishell->input = ret;
	return (0);
}

static int	single_ampersand(t_shell *minishell, int *i) // если будет время, то реализовать
{
	return (syntax_error(minishell, minishell->input[*i]));
}

static int	double_ampersand(t_shell *minishell, int *i)
{
	char	*ret;

	ret = NULL;
	if (*i != 0)
		minishell->apps->argv = expand_argv(minishell, i);
	++(*i);
	minishell->apps->token = TOKEN_AND;
	add_application(minishell);
	while (minishell->input[*i + 1] == ' ' || minishell->input[*i + 1] == '\t')
		++(*i);
	if (minishell->input[*i + 1] == 0 || minishell->input[*i + 1] == '|' ||
		minishell->input[*i + 1] == '<' || minishell->input[*i + 1] == '>' ||
		minishell->input[*i + 1] == '&')
		return (syntax_error(minishell, minishell->input[*i + 1]));
	if (minishell->input[*i] != 0 && minishell->input[*i + 1] != 0)
		ret = ft_strdup(minishell->input + *i + 1);
	(*i) = -1;
	free(minishell->input);
	minishell->input = ret;
	return (0);
}