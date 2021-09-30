/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:32:48 by prochell          #+#    #+#             */
/*   Updated: 2021/09/30 16:55:08 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lst_swap(t_envp *swap)
{
	t_envp	first;
	t_envp	second;
	t_envp	third;
	t_envp	fourth;

	tmp_next =
	tmp_prev =
	max_prev =
	max_prev =
}


int		get_export(t_shell *minishell, char **str)
{
	t_envp	*tmp_env;
	int		cont;

	if (!ft_strncmp("export", str[0], 7))
	{
		tmp_env = minishell->environment;
		cont = 0;
		printf("=============================================\n");
		check_list(tmp_env);
		printf("=============================================\n");
		while (tmp_env)
		{
			if (!tmp_env->next->key)
				break;
			if (ft_strcmp(tmp_env->key, tmp_env->next->key) > 0)
			{
				ft_lst_swap(tmp_env);
				// printf("Here is export\n");
				cont++;
			}
			tmp_env = tmp_env->next;
		}
		if (!cont)
			return (0);
		get_export(minishell, str);
		// printf("Here is export\n");
	}
	return (1);
}
