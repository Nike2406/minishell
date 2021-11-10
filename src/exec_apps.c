/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_apps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:41:29 by signacia          #+#    #+#             */
/*   Updated: 2021/11/10 19:51:32 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pid_error(t_shell *minishell)
{
	dup2(minishell->fd0_source, 0);
	dup2(minishell->fd1_source, 1);
	dup2(minishell->fd2_source, 2);
	return (standard_error(minishell, "fork"));
}

int	shell_executor2(t_shell *minishell)
{
	pid_t	pid;
	int		ret;

	pid = fork();
	if (pid == 0)
	{
		if (minishell->apps->token == IS_PIPE
			&& minishell->apps->output_file == NULL)
		{
			dup2(minishell->apps->fd[1], 1);
			close(minishell->apps->fd[0]);
		}
		if (builtin_exec(minishell))
			;
		else if (execve(get_prog_name(minishell), minishell->apps->argv,
				get_arr_env(minishell->environment)) == -1)
			executing_error(minishell);
		exit (minishell->child_exit_status);
	}
	else if (pid == -1)
		return (pid_error(minishell));
	waitpid(-1, &ret, 0);
	minishell->child_exit_status = WEXITSTATUS(ret);
	return (0);
}

static int	shell_executor(t_shell *minishell)
{
	if (minishell->apps->token == IS_PIPE)
	{
		if (shell_executor2(minishell))
			return (1);
	}
	else if (get_pwd(minishell, minishell->apps->argv) < 1)
		return (0);
	else if (get_echo(minishell, minishell->apps->argv) < 1)
		return (0);
	else if (get_cd(minishell, minishell->apps->argv) < 1)
		return (0);
	else if (get_env(minishell, minishell->apps->argv) < 1)
		return (0);
	else if (get_export(minishell, minishell->apps->argv) < 1)
		return (0);
	else if (get_unset(minishell, minishell->apps->argv) < 1)
		return (0);
	else if (get_exit(minishell, minishell->apps->argv) < 1)
		return (0);
	else
	{
		if (shell_executor2(minishell))
			return (1);
	}
	return (0);
}

void	minishell_executor(t_shell *minishell)
{
	minishell->fd0_source = dup(0);
	minishell->fd1_source = dup(1);
	minishell->fd2_source = dup(2);
	minishell->apps = minishell->apps->head;
	while (1)
	{
		minishell_pre_executor(minishell);
		if (minishell->apps->do_not_launch == 0)
			if (shell_executor(minishell))
				break ;
		minishell_post_executor(minishell);
		if (minishell->apps->next == NULL || (minishell->apps->token
				== TOKEN_OR && minishell->child_exit_status == 0)
			|| (minishell->apps->token == TOKEN_AND
				&& minishell->child_exit_status != 0))
			break ;
		minishell->apps = minishell->apps->next;
	}
	close(minishell->fd0_source);
	close(minishell->fd1_source);
	close(minishell->fd2_source);
}
