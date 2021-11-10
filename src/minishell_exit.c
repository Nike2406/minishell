/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:56:00 by prochell          #+#    #+#             */
/*   Updated: 2021/11/09 16:33:40 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_exit(t_shell *minishell, char **str)
{
	int	len;

	if (!ft_strcmp("exit", str[0]))
	{
		len = 0;
		while (str[len])
			len++;
		if (len > 2)
		{
			write(2, "minishell: exit: too many arguments\n", 36);
			minishell->child_exit_status = 1;
			return (0);
		}
		else if (len == 2)
			exit(ft_atoi(str[len - 1]));
		exit(0);
	}
	return (1);
}
