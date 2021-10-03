/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:32:48 by prochell          #+#    #+#             */
/*   Updated: 2021/10/03 21:18:57 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lst_swap(t_envp **swap)
{
	t_envp	*zero;
	t_envp	*first;
	t_envp	*second;
	t_envp	*third;

	second = NULL;
	if (!(*swap)->next->next)
	{
		*swap = ft_lstfirst_minishell(*swap);
	}
	else if (!(*swap)->prev)
	{
		if ((*swap) == NULL || (*swap)->next == NULL)
			return ;
		first = *swap;
		first->prev = (*swap)->next;
		second = first->next;
		third = second->next;
		third->prev = first;
		second->prev = NULL;
		first->next = third;
		second->next = first;
		*swap = second;
	}
	else
	{
		zero = (*swap)->prev;
		first = *swap;
		first->prev = (*swap)->next;
		second = first->next;
		zero->next = second;
		third = second->next;
		third->prev = first;
		second->prev = zero;
		first->next = third;
		second->next = first;
		*swap = second;
	}
}

int	sort_export(t_envp *tmp_env)
{
	int		cont;

	cont = 0;
	while (tmp_env->next->next)
	{
		if (!tmp_env->next->key)
			break;
		if (ft_strcmp(tmp_env->key, tmp_env->next->key) > 0)
		{
			ft_lst_swap(&tmp_env);
			cont++;
		}
		tmp_env = tmp_env->next;
	}
	if (!cont)
	{
		tmp_env = ft_lstfirst_minishell(tmp_env);
		check_list(tmp_env);
		return (0);
	}
	sort_export(tmp_env);
	return (1);
}

int		get_export(t_shell *minishell, char **str)
{
	t_envp	*tmp_env;

	if (!ft_strncmp("export", str[0], 7))
	{
		tmp_env = minishell->environment;

		if (!sort_export(tmp_env))
		{
			// printf("=============================================\n");
			// check_list(tmp_env);
			// printf("=============================================\n");
			return (0);
		}
		return (1);
	}
	return (1);
}
