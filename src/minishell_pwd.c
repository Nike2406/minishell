/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 16:28:21 by prochell          #+#    #+#             */
/*   Updated: 2021/11/10 16:04:25 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pwd(t_shell *minishell, char **str)
{
	char	tmp[1000];

	if (!ft_strcmp("pwd", str[0]))
	{
		printf("%s\n", getcwd(tmp, sizeof(tmp)));
		minishell->child_exit_status = 0;
		return (0);
	}
	return (1);
}
