/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 16:53:01 by prochell          #+#    #+#             */
/*   Updated: 2021/10/11 14:30:46 by prochell         ###   ########.fr       */
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
	if (i == CD_ERR)
		printf("CD error\n");
	else if (i == CD_CHDIR)
		printf("cd: CHDIR error\n");
	else if (i == CD_CWD)
		printf("cd: CWD error\n");
	return(1);
}

int	ft_error_cd_no_file(int i, char *str)
{
	if (i == CD_NO_FILE)
		printf("cd: %s: No such file or directory\n", str);
	return (1);
}

int	ft_error_export(int i, char *str)
{
	if (i == EXPORT_NOT_VALID)
		printf("export: `%s': not a valid identifier\n", str);
	return (1);
}
