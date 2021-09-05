/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 16:53:01 by prochell          #+#    #+#             */
/*   Updated: 2021/09/05 17:36:06 by prochell         ###   ########.fr       */
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
