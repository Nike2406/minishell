/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 16:28:21 by prochell          #+#    #+#             */
/*   Updated: 2021/09/05 17:28:50 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pwd(t_shell *minishell)
{
	char **tmp;

	tmp = ft_split(minishell->input, ' ');
	if (!ft_strncmp("pwd", tmp[0], 4) && !tmp[1])
	{
		printf("here is pwd\n");
	}
	return (0);
}
