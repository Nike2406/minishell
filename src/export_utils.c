/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 19:46:17 by prochell          #+#    #+#             */
/*   Updated: 2021/10/25 21:31:56 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*fullfill_env(t_envp *env)
{
	t_envp	*tmp;
	t_envp	*tmp_env;

	tmp = NULL;
	tmp_env = env;
	while (tmp_env)
	{
		if (tmp_env->value == NULL)
			tmp_env->value = "";
		ft_lstadd_back_minishell(&tmp, \
			ft_lstnew_minishell(tmp_env->key, tmp_env->value));
		tmp_env = tmp_env->next;
	}
	return (tmp);
}

int	check_export_dup(t_envp *env, char **arr)
{
	t_envp	*tmp_exp;

	tmp_exp = env;
	while (tmp_exp)
	{
		if (!ft_strcmp(tmp_exp->key, arr[0]))
		{
			tmp_exp->value = arr[1];
			return (0);
		}
		tmp_exp = tmp_exp->next;
	}
	ft_lstadd_back_minishell(&env, \
		ft_lstnew_minishell(arr[0], arr[1]));
	return (1);
}

int	check_export(char **str, t_envp *env)
{
	int		i;
	char	**arr;

	i = 1;
	while (str[i])
	{
		arr = ft_split(str[i], '=');
		if (!(ft_isalpha(arr[0][0])) && arr[0][0] != '_')
		{
			ft_error_export(EXPORT_NOT_VALID, str[i]);
			i++;
			free(arr);
			continue;
			// return (1);
		}
		check_export_dup(env, arr);
		i++;
		free(arr);
	}
	return 0;
}
