/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:15:20 by prochell          #+#    #+#             */
/*   Updated: 2021/10/25 20:45:53 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_del_elem(t_envp *tmp_exp, char *str, int f)
{
	while (tmp_exp && !f)
	{
		if (!ft_strcmp(tmp_exp->key, str))
		{
			tmp_exp->prev = ft_lstdelone_minishell(tmp_exp);
			break;
		}
		tmp_exp = tmp_exp->next;
	}
}

int	check_equal(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '=')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	check_unset_params(char **str, t_envp *env)
{
	t_envp	*tmp_exp;
	int	i;
	int	j;
	int	f;

	i = 1;
	while (str[i])
	{
		f = 0;
		j = 0;
		tmp_exp = env;
		while ((!(ft_isalpha(str[i][j])) && (str[i][j] != '_')) || !check_equal(str))
		{
			ft_error_unset(UNSET_NOT_VALID, str[i]);
			f = 1;
			break;
		}
		unset_del_elem(tmp_exp, str[i], f);
		i++;
	}
}

int	get_unset(t_shell *minishell, char **str)
{
	if (!ft_strncmp("unset", str[0], 6))
	{
		if (!str[1])
			return (0);
		else
			check_unset_params(str, minishell->environment);
		return (0);
	}
	return (1);
}
