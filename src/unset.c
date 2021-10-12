/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:15:20 by prochell          #+#    #+#             */
/*   Updated: 2021/10/12 15:55:21 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		while (!(ft_isalpha(str[i][j])) && str[i][j] != '_')
		{
			ft_error_unset(UNSET_NOT_VALID, str[i]);
			f = 1;
			break;
		}
		while (tmp_exp && !f)
		{
			if (!ft_strcmp(tmp_exp->key, str[i]))
			{
				tmp_exp->prev = ft_lstdelone_minishell(tmp_exp);
				break;
			}
		tmp_exp = tmp_exp->next;
		}
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
