/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 00:04:48 by prochell          #+#    #+#             */
/*   Updated: 2021/09/04 00:36:29 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***get_envp(char **env)
{
	char	***tmp;

	tmp = NULL;
	printf("%s", env[2]);

	// int i;
	// int j;
	// int	m;
	// i = 0;
	// while (env[i])
	// {
	// 	j = 0;
	// 	while (env[i][j])
	// 		tmp[i][j] = env[i][j];
	// }

	return (tmp);
}
