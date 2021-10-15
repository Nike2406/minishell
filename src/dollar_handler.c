/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:46:16 by signacia          #+#    #+#             */
/*   Updated: 2021/10/06 15:46:17 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*dollar_child_status(t_shell *minishell, int *i, int j)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

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

static char	*dollar_is_space(t_shell *minishell, int *i)
{
	*i -= 1;
	return (minishell->input);
}

static char	*dollar_cases(t_shell *minishell, int *i, int j)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(minishell->input, 0, j);
	tmp2 = ft_strdup(minishell->input + *i + 1);
	tmp = ft_strjoin_free(tmp, tmp2);
	free(minishell->input);
	*i -= 2;
	return (tmp);
}

static char	*dollar_env(t_shell *minishell, int *i, int j)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	while (ft_isalnum(minishell->input[*i]) || minishell->input[*i] == '_')
		(*i)++;
	tmp = ft_substr(minishell->input, 0, j);
	tmp2 = ft_substr(minishell->input, j + 1, *i - j - 1); //ЗАМЕНИТЬ env'ОМ!
	// Также нужен будет сдвиг *i
	tmp3 = ft_strdup(minishell->input + *i);
	tmp2 = ft_strjoin_free(tmp2, tmp3);
	tmp = ft_strjoin_free(tmp, tmp2);
	free(minishell->input);
	*i -= 2;
	return (tmp);
}

char	*dollar(t_shell *minishell, int *i)
{
	int		j;

	j = *i;
	++(*i);
	if (minishell->input[*i] == '?')
		return (dollar_child_status(minishell, i, j));
	else if (minishell->input[*i] == ' ' || minishell->input[*i] == '\t')
		return (dollar_is_space(minishell, i));
	else if (ft_isdigit(minishell->input[*i]) || minishell->input[*i] == '\''
			|| minishell->input[*i] == '\"')
		return (dollar_cases(minishell, i, j));
	else
		return (dollar_env(minishell, i, j));
}