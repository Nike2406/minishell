/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:04:41 by signacia          #+#    #+#             */
/*   Updated: 2021/11/08 17:26:28 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(t_shell *minishell, const char *token, int len)
{
	write(2, "minishell: ", 11);
	if (token[0] == 0)
		write(2, "syntax error near unexpected token `newline'\n", 45);
	else
	{
		write(2, "syntax error near unexpected token `", 36);
		write(2, token, len);
		write(2, "'\n", 2);
	}
	minishell->child_exit_status = 258;
	return (1);
}

int	standard_error(t_shell *minishell, char *arg_name)
{
	write(2, "minishell: ", 11);
	perror(arg_name);
	minishell->child_exit_status = 1;
	minishell->apps->do_not_launch = 1;
	minishell->apps->token = 0;
	return (1);
}

int	executing_error(t_shell *minishell)
{
	write(2, "minishell: ", 11);
	write(2, minishell->apps->argv[0], ft_strlen(minishell->apps->argv[0]));
	write(2, ": command not found\n", 20);
	exit(127);
}
