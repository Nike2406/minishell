/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 16:53:01 by prochell          #+#    #+#             */
/*   Updated: 2021/11/12 17:52:23 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_cd(t_shell *minishell)
{
	perror("minishell: cd");
	minishell->child_exit_status = 1;
	return (0);
}

int	ft_error_cd_home_not_set(t_shell *minishell)
{
	char	*str;

	str = "minishell: cd: HOME not set\n";
	write(2, str, ft_strlen(str));
	minishell->child_exit_status = 1;
	return (0);
}

int	ft_error_cd_no_file(t_shell *minishell, char *str)
{
	write(2, "minishell: cd: ", 15);
	perror(str);
	minishell->child_exit_status = 1;
	return (0);
}

int	ft_error_export(t_shell *minishell, char *str)
{
	write(2, "minishell: export: `", 20);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 26);
	minishell->child_exit_status = 1;
	return (0);
}

int	ft_error_unset(t_shell *minishell, char *str)
{
	write(2, "minishell: unset: `", 19);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 26);
	minishell->child_exit_status = 1;
	return (0);
}
