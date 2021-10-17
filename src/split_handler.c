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

char	**updating_matches(char *input, char **argv, int *argc)
{
	int			k;
	char		**tmp;

	k = 0;
	tmp = (char **)malloc(sizeof(char *) * (++(*argc) + 1));
	while (k < *argc - 1)
	{
		tmp[k] = argv[k];
		k++;
	}
	if (argv != NULL)
		free(argv);
	tmp[k] = ft_strdup(input);
	tmp[k + 1] = NULL;
	return (tmp);
}

void	search_half_matches(char *pattern, char *d_name, int *k, int *j)
{
	int		tmp_k;
	int		tmp_j;

	tmp_k = *k;
	tmp_j = *j;
	while (1)
	{
		++(*k);
		++(*j);
		if (pattern[*k] == '*' || (pattern[*k] == 0 && d_name[*j] == 0))
			return ;
		if (pattern[*k] != d_name[*j])
		{
			*k = tmp_k;
			*j = tmp_j;
			return ;
		}
	}
}

char	**search_matches(t_shell *minishell, int *i)
{

	DIR				*dir;
	struct dirent	*tmp;
	char			**ret;
	int				k;
	int				j;
	int				argc;
	char			*pattern;

	pattern = ft_substr(minishell->input, 0, *i);
	argc = 0;
	ret = NULL;
	// dir = opendir(getenv("PWD")); // заменить на свой getenv!!!!!!!!!!!!!!
	dir = opendir(ft_getenv(minishell->environment, "PWD"));
	if (dir != NULL)
	{
		tmp = readdir(dir);
		while (tmp)
		{
			k = 0;
			j = 0;
			while (1)
			{
				if ((pattern[0] != '*' && pattern[0] != tmp->d_name[0])
					|| (tmp->d_name[0] == '.' && pattern[0] != '.'))
					break ;
				if (pattern[k] == tmp->d_name[j])
					search_half_matches(pattern, tmp->d_name, &k, &j);
				if (pattern[k] == '*')
					k++;
				else if (pattern[k] == 0)
				{
					ret = updating_matches(tmp->d_name, ret, &argc);
					break ;
				}
				else if (tmp->d_name[j] == 0)
					break ;
				else
					j++;
			}
			tmp = readdir(dir);
		}
		closedir(dir);

	}
	if (ret == NULL)
	{
		ret = malloc(sizeof(char *));
		ret[0] = pattern;
	}
	else if (pattern != NULL)
		free(pattern);
	return (ret);
}

char	**expand_argv_wildcard(t_shell *minishell, int *i)
{
	int		k;
	int		j;
	char	**tmp;
	char	**tmp_cards;

	tmp_cards = search_matches(minishell, i);
	k = -1;
	j = 0;
	tmp = (char **)malloc(sizeof(char *) * (++(minishell->apps->argc) + 100)); // исправить
	while (++k < minishell->apps->argc - 1)
		tmp[k] = minishell->apps->argv[k];
	while (tmp_cards != NULL && tmp_cards[j] != NULL)
		tmp[k++] = tmp_cards[j++];
	tmp[k] = NULL;
	if (minishell->apps->argv != NULL)
		free(minishell->apps->argv);
	if (tmp_cards != NULL)
		free(tmp_cards);
	minishell->apps->is_argv = 1;

	int d = 0;
	while (tmp[d] != 0)
		{printf("tmp[%d]=[%s]\n", d, tmp[d]);
		d++;}
	return (tmp);
}

// Expanding argv and adding new element in its end.
char	**expand_argv(t_shell *minishell, int *i)
{
	int			k;
	char		**tmp;

	if (minishell->apps->token == WILDCARD_ASTERISK)
		return (expand_argv_wildcard(minishell, i));
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
	minishell->apps->is_argv = 1;
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