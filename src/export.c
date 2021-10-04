/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:32:48 by prochell          #+#    #+#             */
/*   Updated: 2021/10/04 19:40:42 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lst_swap(t_envp **swap)
{
	t_envp	*zero;
	t_envp	*first;
	t_envp	*second;
	t_envp	*third;

	// (((*swap)->next)->next) = NULL;
	second = NULL;
	if (!(*swap)->prev)
	{
		// (*cont)++;
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
		// (*cont)++;
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
	// int count;
	int i;
	int j;
	int list_size;

	// count = -1;
	list_size = 0;
	while (tmp_env->next)
	{
		tmp_env = tmp_env->next;
		list_size++;
	}

	i = 0;
	while (i < list_size - 1)
	{
		j = 0;
		tmp_env = ft_lstfirst_minishell(tmp_env);
		while (j < list_size - i - 1)
		{
			if (ft_strcmp(tmp_env->key, tmp_env->next->key) > 0)
			{
				ft_lst_swap(&tmp_env);
			}
			tmp_env = tmp_env->next;
			j++;
		}
		i++;
	}
	check_list(tmp_env);

	// while (tmp_env->next)
	// {
	// 	count = 0;
	// 	tmp_env = head;
	// 	if (ft_strcmp(tmp_env->key, tmp_env->next->key) > 0)
	// 	{
	// 		// if (!tmp_env->next->next)
	// 		// {
	// 		// 	tmp_env = head;
	// 		// 	count = 0;
	// 		// 	continue;
	// 		// }
	// 		ft_lst_swap(&tmp_env, &count);
	// 	}
	// 	if (!count)
	// 	{
	// 		check_list(tmp_env);
	// 		break;
	// 	}
	// 	tmp_env = tmp_env->next;
	// }

	return (1);
	// int	cont;

	// cont = 0;
	// while (tmp_env->next)
	// {
	// 	if (!tmp_env->next->key)
	// 		break;
	// 	if (ft_strcmp(tmp_env->key, tmp_env->next->key) > 0)
	// 	{
	// 		ft_lst_swap(&tmp_env, &cont);
	// 	}
	// 	if (!cont)
	// 		break;
	// 	tmp_env = tmp_env->next;
	// }
	// if (!cont)
	// {
	// 	tmp_env = ft_lstfirst_minishell(tmp_env);
		// check_list(tmp_env);
	// 	return (0);
	// }
	// sort_export(tmp_env);
	// return (1);

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
