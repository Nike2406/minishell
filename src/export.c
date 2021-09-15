/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:32:48 by prochell          #+#    #+#             */
/*   Updated: 2021/09/15 21:10:52 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_export(t_shell *minishell, char **str)
{
	(void)str;
	t_envp	*tmp_env;

	if (!ft_strncmp("export", str[0], 7))
	{
		tmp_env = minishell->environment;

		while (tmp_env)
		{
			if (tmp_env->key ft_strncmp)
		}
		printf("Here is export\n");
		return (0);
	}
	return (1);
}
