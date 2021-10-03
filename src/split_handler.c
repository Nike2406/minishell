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
	// printf("input=[%s]\n", ret);
	return (ret);
}

char	*space_cut(t_shell *minishell, int *i)
{
	int		k;
	char	*ret;
	char	**tmp;

	k = 0;
	ret = NULL;
	tmp = (char **)malloc(sizeof(char *) * (++(minishell->apps->argc) + 1));
	while (k < minishell->apps->argc - 1)
	{
		tmp[k] = ft_strdup(minishell->apps->argv[k]);
		free(minishell->apps->argv[k]);
		k++;
	}
	if (minishell->apps->argv != NULL)
		free(minishell->apps->argv);
	tmp[k] = ft_substr(minishell->input, 0, *i);
	tmp[k + 1] = NULL;
	minishell->apps->argv = tmp;
	while (minishell->input[*i + 1] == ' ' || minishell->input[*i + 1] == '\t')
		++(*i);
	if (minishell->input[*i] != 0 && minishell->input[*i + 1] != 0)
		ret = ft_strdup(minishell->input + *i + 1);
	(*i) = -1;
	free(minishell->input);

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