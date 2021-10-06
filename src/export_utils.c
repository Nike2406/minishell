/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 19:46:17 by prochell          #+#    #+#             */
/*   Updated: 2021/10/06 19:46:43 by prochell         ###   ########.fr       */
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
		ft_lstadd_back_minishell(&tmp, \
			ft_lstnew_minishell(tmp_env->key, tmp_env->value));
		tmp_env = tmp_env->next;
	}
	return (tmp);
}
