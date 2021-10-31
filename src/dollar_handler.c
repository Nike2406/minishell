/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:46:16 by signacia          #+#    #+#             */
/*   Updated: 2021/10/31 16:30:25 by prochell         ###   ########.fr       */
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
	char	*env_value;

	while (ft_isalnum(minishell->input[*i]) || minishell->input[*i] == '_')
		(*i)++;
	tmp = ft_substr(minishell->input, 0, j);
	tmp2 = ft_substr(minishell->input, j + 1, *i - j - 1);
	env_value = ft_getenv_value(minishell->environment, tmp2);
	tmp3 = ft_strdup(minishell->input + *i);
	*i += ft_strlen(env_value) - ft_strlen(tmp2) - 2;
	free(tmp2);
	tmp2 = ft_strjoin(env_value, tmp3);
	free(tmp3);
	tmp = ft_strjoin_free(tmp, tmp2);
	free(minishell->input);
	//*i -= 2; // нарисовал выше
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