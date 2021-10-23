#include "minishell.h"

int	space_cut_begin(t_shell *minishell)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (minishell->input[i] == ' ' || minishell->input[i] == '\t')
		i++;
	if (minishell->input[i] == '|' || minishell->input[i] == '&')
	{
		if (minishell->input[i] == minishell->input[i + 1])
			return (syntax_error(minishell, minishell->input + i, 2));
		return (syntax_error(minishell, minishell->input + i, 1));
	}
	if (minishell->input[i] != 0)
		ret = ft_strdup(minishell->input + i);
	free(minishell->input);
	minishell->input = ret;
	return (0);
}

static char	**upd_matches(t_asterisk *astr, char **argv)
{
	int			k;
	char		**tmp;

	k = 0;
	tmp = (char **)malloc(sizeof(char *) * (++(astr->argc) + 1));
	while (k < astr->argc - 1)
	{
		tmp[k] = argv[k];
		k++;
	}
	if (argv != NULL)
		free(argv);
	tmp[k] = ft_strdup(astr->cmp->d_name);
	tmp[k + 1] = NULL;
	return (tmp);
}

static int	search_half_matches(char *pattern, t_asterisk *astr)
{
	int		tmp_k;
	int		tmp_j;

	if (pattern[astr->k] == astr->cmp->d_name[astr->j] && pattern[astr->k])
	{
		tmp_k = astr->k;
		tmp_j = astr->j;
		while (1)
		{
			++(astr->k);
			++(astr->j);
			if (pattern[astr->k] == '*' || (pattern[astr->k] == 0 && astr->cmp->d_name[astr->j] == 0))
				break ;
			if (pattern[astr->k] != astr->cmp->d_name[astr->j])
			{
				astr->k = tmp_k;
				astr->j = tmp_j;
				break ;
			}
		}
	}
	return (1);
}

static char	**lonely_pattern(char *pattern, t_asterisk	*astr)
{
	char	**ret;

	ret = (char **)malloc(sizeof(char *) * 2);
	ret[0] = pattern;
	ret[1] = NULL;
	astr->argc++;
	return (ret);
}


static void	compare_matches(t_asterisk *astr, char *pattern, char ***ret)
{
	astr->cmp = readdir(astr->dir);
	while (astr->cmp)
	{
		astr->k = 0;
		astr->j = 0;
		while (1)
		{
			if ((pattern[0] != '*' && pattern[0] != astr->cmp->d_name[0])
				|| (astr->cmp->d_name[0] == '.' && pattern[0] != '.'))
				break ;
			search_half_matches(pattern, astr);
			if (pattern[astr->k] == '*')
				astr->k++;
			else if (pattern[astr->k] == 0)
			{
				*ret = upd_matches(astr, *ret);
				break ;
			}
			else if (astr->cmp->d_name[astr->j] == 0)
				break ;
			else
				astr->j++;
		}
		astr->cmp = readdir(astr->dir);
	}
}

static char	**search_matches(t_shell *minishell, int *i, t_asterisk	*astr)
{
	char	**ret;
	char	*pattern;

	pattern = ft_substr(minishell->input, 0, *i);
	if (pattern[0] == '/')
		return (lonely_pattern(pattern, astr));
	ret = NULL;
	astr->dir = opendir(ft_getenv(minishell->environment, "PWD"));
	if (astr->dir != NULL)
	{
		compare_matches(astr, pattern, &ret);
		closedir(astr->dir);

		// int d = 0;
		// while (ret[d] != 0)
		// {
		// 	printf("tmp[%d]=[%s]\n", d, ret[d]);
		// 	d++;
		// }
		// printf("argc=[%d]\n", astr->argc);
	}
	if (ret == NULL)
		return (lonely_pattern(pattern, astr));
	free(pattern);
	return (ret);
}

static t_asterisk	create_astr(void)
{
	t_asterisk	astr;

	astr.dir = NULL;
	astr.cmp = NULL;
	astr.k = 0;
	astr.j = 0;
	astr.argc = 0;
	return (astr);
}

char	**expand_argv_wildcard(t_shell *minishell, int *i)
{
	int			k;
	int			j;
	char		**tmp;
	char		**tmp_cards;
	t_asterisk	astr;

	astr = create_astr();
	tmp_cards = search_matches(minishell, i, &astr);
	k = -1;
	j = 0;
	// printf("orig=%d astr=%d, total=%d\n", minishell->apps->argc, astr.argc, minishell->apps->argc + astr.argc);
	minishell->apps->argc += astr.argc;
	tmp = (char **)malloc(sizeof(char *) * (minishell->apps->argc + 1));
	while (minishell->apps->argv != NULL && minishell->apps->argv[++k] != NULL)
	{
		// printf("minishell[%d]=[%s]\n", k, minishell->apps->argv[k]);
		tmp[k] = minishell->apps->argv[k];
	}
	while (tmp_cards != NULL && tmp_cards[j] != NULL)
	{
		// printf("tmp_cards[%d]=[%s]\n", j, tmp_cards[j]);
		tmp[k++] = tmp_cards[j++];
	}
	tmp[k] = NULL;
	if (minishell->apps->argv != NULL)
		free(minishell->apps->argv);
	if (tmp_cards != NULL)
		free(tmp_cards);

	// int d = 0;
	// while (tmp[d] != 0)
	// 	{printf("tmp[%d]=[%s]\n", d, tmp[d]);
	// 	d++;}
	minishell->apps->token = 0;
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