/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 16:28:21 by prochell          #+#    #+#             */
/*   Updated: 2021/09/05 17:49:56 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pwd(t_shell *minishell)
{
	char 	**tmp;
	t_envp	*tmp_env;

	tmp = ft_split(minishell->input, ' ');
	tmp_env = minishell->environment;
	if (tmp[1])
		ft_error_pwd(PWD_ERR_OVERWELMING);
	else if (!ft_strncmp("pwd", tmp[0], 4) && !tmp[1])
	{
		while (tmp_env)
		{
			if (!ft_strncmp("PWD", tmp_env->key, 4))
			{
				printf("%s\n", tmp_env->value);
				free(tmp);
				return (0);
			}
			tmp_env = tmp_env->next;
		}
	}
	free(tmp);
	return (1);
}
