/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 16:17:24 by prochell          #+#    #+#             */
/*   Updated: 2021/10/31 17:12:25 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_shlvl(t_shell *minishell)
{
	t_envp	*tmp;
	int		shlvl;


	shlvl = ft_atoi(ft_getenv_value(minishell->environment, "SHLVL"));
	tmp = minishell->environment;
	if (!minishell->input)
		return ;
	if (shlvl < 0)
	{
		while (tmp)
		{
			if (!(ft_strcmp(tmp->key, "SHLVL")))
			{
				tmp->value = "0";
				break;
			}
			tmp = tmp->next;
		}
	}
	else if (!(ft_strcmp(minishell->input, "./minishell")))
	{
		while (tmp)
		{
			if (!(ft_strcmp(tmp->key, "SHLVL")))
			{
				tmp->value = ft_itoa(ft_atoi(tmp->value) + 1);
				break;
			}
			tmp = tmp->next;
		}
	}
}
