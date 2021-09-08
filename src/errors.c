/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 16:53:01 by prochell          #+#    #+#             */
/*   Updated: 2021/09/07 21:34:37 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_pwd(int i)
{
	if (i == PWD_ERR)
		printf("PWD error\n");
	else if (i == PWD_ERR_OVERWELMING)
		printf("pwd: too many arguments\n");
	return(1);
}

int	ft_error_cd(int i)
{
	if (i == PWD_ERR)
		printf("CD error\n");
	else if (i == PWD_ERR_OVERWELMING)
		printf("cd: string not in pwd: ..\n");
	return(1);
}
