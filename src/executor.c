#include "minishell.h"

char	*get_prog_name(t_shell *minishell)
{
	int		i;
	char	*tmp;
	char	*ret;
	char	**paths;

	ret = minishell->apps->argv[0];
	paths = ft_split(ft_getenv_value(minishell->environment, "PATH"), ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin("/", minishell->apps->argv[0]);
		tmp = ft_strjoin_free(paths[i], tmp);
		if (access(tmp, 0) == 0)
			ret = tmp;
		else
			free(tmp);
		i++;
	}
	free(paths);
	return (ret);
}

static int	builtin_exec(t_shell *minishell)
{
// 		if (minishell->apps->output_file != NULL)
// 			dup2(minishell->apps->fd_output_file, 1); // надо закрывать, если произошла ошибка исполнения программы?
// 		if (minishell->apps->input_file != NULL || minishell->apps->heredoc != NULL)
// 			dup2(minishell->apps->fd_input_file, 0); // если файл не найден, то запуска быть не должно; надо закрывать, если произошла ошибка исполнения программы?

// 		if (minishell->apps->token == TOKEN_PIPE && minishell->apps->output_file == NULL)
// 		{
// 			dup2(minishell->apps->fd[1], 1);
// 			close(minishell->apps->fd[0]);
// 		}

	if (get_pwd(minishell, minishell->apps->argv) < 1)
		return (1);
	else if (get_echo(minishell->apps->argv) < 1)
		return (1);
	else if (get_cd(minishell, minishell->apps->argv) < 1)
		return (1);
	else if (get_env(minishell, minishell->apps->argv) < 1)
		return (1);
	else if (get_export(minishell, minishell->apps->argv) < 1)
		return (1);
	else if (get_unset(minishell, minishell->apps->argv) < 1)
		return (1);
	else if (get_exit(minishell, minishell->apps->argv) < 1)
		return (1);
	return (0);
}

int	shell_pre_executor(t_shell *minishell)
{
	if (minishell->apps->token == TOKEN_PIPE)
	{
		if (pipe(minishell->apps->fd))
			return (standard_error(minishell, NULL));
	}
	return (0);
}

int	shell_executor(t_shell *minishell)
{
	pid_t	pid;
	int		ret;

	pid = fork();
	if (pid == 0)
	{
		check_shlvl(minishell);
		if (minishell->apps->output_file != NULL)
			dup2(minishell->apps->fd_output_file, 1); // надо закрывать, если произошла ошибка исполнения программы?
		if (minishell->apps->input_file != NULL || minishell->apps->heredoc != NULL)
			dup2(minishell->apps->fd_input_file, 0); // если файл не найден, то запуска быть не должно; надо закрывать, если произошла ошибка исполнения программы?

		if (minishell->apps->token == TOKEN_PIPE && minishell->apps->output_file == NULL)
		{
			dup2(minishell->apps->fd[1], 1);
			close(minishell->apps->fd[0]);
		}
		execve(get_prog_name(minishell), minishell->apps->argv, get_arr_env(minishell->environment));
		executing_error(minishell);
		exit(127);
	}
	else if (pid == -1)
	{
		dup2(minishell->fd0_source, 0);
		dup2(minishell->fd1_source, 1);
		dup2(minishell->fd2_source, 2);
		return (standard_error(minishell, "fork"));
	}
	waitpid(-1, &ret, 0);
	minishell->child_exit_status = WEXITSTATUS(ret);





	return (0);
}

int	shell_post_executor(t_shell *minishell)
{
	if (minishell->apps->token == TOKEN_PIPE)
	{
		dup2(minishell->apps->fd[0], 0);
		close(minishell->apps->fd[1]);
		// close(minishell->apps->fd[0]);
	}

	// if (minishell->apps->token == TOKEN_OR && minishell->child_exit_status == 0) // для || and &&
	// 	minishell->apps->do_not_launch = 1;
	// else if (minishell->apps->token == TOKEN_AND && minishell->child_exit_status != 0)
	// 	minishell->apps->do_not_launch = 1;


	if (minishell->apps->token == 0)
	{
		dup2(minishell->fd0_source, 0);
		dup2(minishell->fd1_source, 1);
		dup2(minishell->fd2_source, 2);
	}
	if (minishell->apps->output_file != NULL)
	{
		close(minishell->apps->fd_output_file);
		dup2(minishell->fd1_source, 1); // надо закрывать, если произошла ошибка исполнения программы?
	}
	if (minishell->apps->input_file != NULL)
	{
		close(minishell->apps->fd_input_file); // если файл не найден, то запуска быть не должно; надо закрывать, если произошла ошибка исполнения программы?
		// dup2(minishell->fd0_source, 0);
	}
	if (minishell->apps->heredoc != NULL)
	{
		close(minishell->apps->fd[0]);
		// dup2(minishell->fd0_source, 0);
	}
	return (0);
}

int	minishell_executor(t_shell *minishell)
{
	minishell->apps = minishell->apps->head;
	while (1)
	{
		if (minishell->apps->do_not_launch == 1) // если установлен флаг "не запускать", апп не запустится, это нужно при наличии ошибок в "<", когда файла не существует
		{
			if (minishell->apps->next == NULL)
				break ;
			else
			{
				minishell->apps = minishell->apps->next;
				continue ;
			}
		}
		shell_pre_executor(minishell);
		if (builtin_exec(minishell));
		else
			shell_executor(minishell);
		shell_post_executor(minishell);
		if (minishell->apps->next == NULL)
			break;
		minishell->apps = minishell->apps->next;
	}
	return (0);
}