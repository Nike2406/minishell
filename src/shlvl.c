/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 16:17:24 by prochell          #+#    #+#             */
/*   Updated: 2021/10/31 16:31:37 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_shlvl(t_shell *minishell)
{
	t_envp	*tmp;

	if (ft_getenv_value(minishell->environment, "SHLVL") < 0)
	{
		tmp = minishell->environment;
		while (tmp)
		{
			if (!(ft_strcmp(tmp->key, "SHLVL")))
			{
				tmp->value = 0;
				break;
			}
			tmp = tmp->next;
		}
	}
	else if (!(ft_strcmp(minishell->input, "./minishell")))
	{
		tmp = minishell->environment;
		while (tmp)
		{
			if (!(ft_strcmp(tmp->key, "SHLVL")))
			{
				tmp->value = tmp->value++;
				break;
			}
			tmp = tmp->next;
		}
	}
}
