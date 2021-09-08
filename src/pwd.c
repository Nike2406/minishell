/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 16:28:21 by prochell          #+#    #+#             */
/*   Updated: 2021/09/08 23:10:04 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pwd(t_shell *minishell, char **str)
{
	char	tmp[1000];

	(void)minishell;
	(void)str;
	if (!ft_strncmp("pwd", str[0], 4))
	 {
		printf("%s\n", getcwd(tmp, sizeof(tmp)));// find_pwd(minishell);
	 }
	// t_envp	*tmp_env;

	// tmp_env = minishell->environment;
	// if (!ft_strncmp("pwd", str[0], 4))
	// {
	// 	if (str[1])
	// 		ft_error_pwd(PWD_ERR_OVERWELMING);
	// 	else
	// 	{
	// 		while (tmp_env)
	// 		{
	// 			if (!ft_strncmp("PWD", tmp_env->key, 4))
	// 			{
	// 				printf("%s\n", tmp_env->value);
	// 				free(str);
	// 				return (0);
	// 			}
	// 			tmp_env = tmp_env->next;
	// 		}
	// 	}
	// }
	return (1);
}
