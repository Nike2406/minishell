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
		if (pipe(minishell->apps->fd))
			return (standard_error(minishell, NULL));
	if (minishell->apps->output_file != NULL)
		dup2(minishell->apps->fd_output_file, 1); // надо закрывать, если произошла ошибка исполнения программы?
	if (minishell->apps->input_file != NULL)
		dup2(minishell->apps->fd_input_file, 0); // если файл не найден, то запуска быть не должно; надо закрывать, если произошла ошибка исполнения программы?
	if (minishell->apps->heredoc != NULL)
		dup2(minishell->apps->fd_heredoc[0], 0); // если файл не найден, то запуска быть не должно; надо закрывать, если произошла ошибка исполнения программы?
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
		if (minishell->apps->token == TOKEN_PIPE && minishell->apps->output_file == NULL)
		{
			dup2(minishell->apps->fd[1], 1);
			close(minishell->apps->fd[0]);
		}
		if (builtin_exec(minishell));
		else if (execve(get_prog_name(minishell), minishell->apps->argv,
				get_arr_env(minishell->environment)) == -1)
			executing_error(minishell);
		exit (0);
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

static void	shell_executor2(t_shell *minishell)
{

	if (get_pwd(minishell, minishell->apps->argv) < 1)
		return ;
	else if (get_echo(minishell->apps->argv) < 1)
		return ;
	else if (get_cd(minishell, minishell->apps->argv) < 1)
		return ;
	else if (get_env(minishell, minishell->apps->argv) < 1)
		return ;
	else if (get_export(minishell, minishell->apps->argv) < 1)
		return ;
	else if (get_unset(minishell, minishell->apps->argv) < 1)
		return ;
	else if (get_exit(minishell, minishell->apps->argv) < 1)
		return ;
	else
		shell_executor(minishell);
}

int	shell_post_executor(t_shell *minishell)
{
	if (minishell->apps->token == TOKEN_PIPE)
	{
		dup2(minishell->apps->fd[0], 0);
		close(minishell->apps->fd[1]);
	}
	// if (minishell->apps->token == TOKEN_OR && minishell->child_exit_status == 0) // для || and &&
	// 	minishell->apps->do_not_launch = 1;
	// else if (minishell->apps->token == TOKEN_AND && minishell->child_exit_status != 0)
	// 	minishell->apps->do_not_launch = 1;
	if (minishell->apps->token != TOKEN_PIPE)
	{
		dup2(minishell->fd0_source, 0);
		dup2(minishell->fd1_source, 1);
		dup2(minishell->fd2_source, 2);
	}
	if (minishell->apps->output_file != NULL)
		close(minishell->apps->fd_output_file);
	if (minishell->apps->input_file != NULL)
		close(minishell->apps->fd_input_file);
	if (minishell->apps->heredoc != NULL)
	{
		close(minishell->apps->fd[0]);
		dup2(minishell->fd0_source, 0);
	}
	return (0);
}

void	minishell_executor(t_shell *minishell)
{
	int	is_pipe;

	minishell->fd0_source = dup(0);
	minishell->fd1_source = dup(1);
	minishell->fd2_source = dup(2);
	minishell->apps = minishell->apps->head;
	is_pipe = 0;
	if (minishell->apps->token == TOKEN_PIPE)
		is_pipe = 1;
	while (1)
	{
		shell_pre_executor(minishell);
		if (minishell->apps->do_not_launch == 0)
		{
			if (is_pipe)
				shell_executor(minishell);
			else
				shell_executor2(minishell);
		}
		shell_post_executor(minishell);
		if (minishell->apps->next == NULL)
			break;
		minishell->apps = minishell->apps->next;
	}
	close(minishell->fd0_source);
	close(minishell->fd1_source);
	close(minishell->fd2_source);
}