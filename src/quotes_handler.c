/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:46:03 by signacia          #+#    #+#             */
/*   Updated: 2021/10/06 15:46:04 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*single_quote(t_shell *minishell, int *i)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		j;

	j = *i;
	while (minishell->input[++(*i)])
	{
		if (minishell->input[*i] == '\'')
			break ;
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
		else if (minishell->input[*i] == '$'
				&& minishell->input[*i + 1] != '\"')
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
