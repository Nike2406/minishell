#include "minishell.h"

char	*single_quote(char *input, int *i)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		j;

	j = *i;
	while (input[++(*i)])
	{
		if (input[*i] == '\'')
			break ;
	}
	tmp = ft_substr(input, 0, j);
	tmp2 = ft_substr(input, j + 1, *i - j - 1);
	tmp3 = ft_strdup(input + *i + 1);
	tmp2 = ft_strjoin_free(tmp2, tmp3);
	tmp = ft_strjoin_free(tmp, tmp2);
	free(input);
	*i -= 2;
	return (tmp);
}

char	*double_quote(t_shell *minishell, int *i)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		j;

	j = *i;
	while (minishell->input[++(*i)])
	{
		if (minishell->input[*i] == '\"')
			break ;
		if (minishell->input[*i] == '$')
			minishell->input = dollar(minishell, i);
	}
	tmp = ft_substr(minishell->input, 0, j);
	tmp2 = ft_substr(minishell->input, j + 1, *i - j - 1);
	tmp3 = ft_strdup(minishell->input + *i + 1);
	tmp2 = ft_strjoin_free(tmp2, tmp3);
	tmp = ft_strjoin_free(tmp, tmp2);
	free(minishell->input);
	*i -= 2;
	return (tmp);
}

char	*dollar(t_shell *minishell, int *i)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		j;

	j = *i;
	if (minishell->input[++(*i)] == '?')
	{
		printf("%c\n", minishell->input[*i]);
		tmp = ft_substr(minishell->input, 0, j);
		tmp2 = ft_itoa(minishell->child_exit_status);
		j = ft_strlen(tmp2);
		tmp3 = ft_strdup(minishell->input + *i + 1);
		tmp2 = ft_strjoin_free(tmp2, tmp3);
		tmp = ft_strjoin_free(tmp, tmp2);
		free(minishell->input);
		*i += j - 2;
		return (tmp);
	}
	if (minishell->input[*i] == ' ' || minishell->input[*i] == '\t')
	{
		*i -= 1;
		return (minishell->input);
	}
	if (ft_isdigit(minishell->input[*i]))
	{
		tmp = ft_substr(minishell->input, 0, j);
		tmp2 = ft_strdup(minishell->input + *i + 1);
		tmp = ft_strjoin_free(tmp, tmp2);
		free(minishell->input);
		*i -= 2;
		return (tmp);
	}
	while (minishell->input[*i] != 0 && (ft_isalnum(minishell->input[*i])
			|| minishell->input[*i] == '_'))
	{
		(*i)++;
	}
	tmp = ft_substr(minishell->input, 0, j);
	tmp2 = ft_substr(minishell->input, j + 1, *i - j - 1); //заменить env'ом
	tmp3 = ft_strdup(minishell->input + *i + 1);
	printf("tmp1=[%s] tmp2=[%s] tmp3=[%s]\n", tmp, tmp2, tmp3);
	return (minishell->input);
}