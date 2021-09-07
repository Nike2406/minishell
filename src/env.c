/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 00:04:48 by prochell          #+#    #+#             */
/*   Updated: 2021/09/06 23:39:42 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_envp(char **env, t_shell *minishell)
{
	char	**tmp;
	int		i;

	i = 0;
	while (env[i])
	{
		tmp = ft_split(env[i], '=');
		ft_lstadd_back_minishell(&minishell->environment, \
			ft_lstnew_minishell(tmp[0], tmp[1]));
		i++;
		free(tmp);
	}
}
