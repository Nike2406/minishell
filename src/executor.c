#include "minishell.h"

char	*get_prog_name(t_shell *minishell)
{
	int				i;
	DIR				*dir;
	struct dirent	*tmp;
	char			*ret;
	char			**paths;

	paths = ft_split(ft_getenv_value(minishell->environment, "PATH"), ':');
	i = 0;
	while (paths[i])
	{
		dir = opendir(paths[i]);
		if (dir != NULL)
		{
			tmp = readdir(dir);
			while (tmp)
			{
				if (ft_strcmp(minishell->apps->argv[0], tmp->d_name) == 0)
				{
					ret = ft_strjoin("/", minishell->apps->argv[0]);
					ret = ft_strjoin_free(paths[i], ret);
					return (ret);
				}
				tmp = readdir(dir);
			}
			closedir(dir);
		}
		i++;
	}
	return (minishell->apps->argv[0]);
}

static int	builtin_execute(t_shell *minishell)
{
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

void	minishell_executor(t_shell *minishell)
{
	minishell->child_exit_status = 0;
	pid_t	pid;
	if (builtin_execute(minishell))
		return ;
	minishell->apps = minishell->apps->head;
	while (1)
	{
		pid = fork();
		if (pid == 0)
		{
			if (minishell->apps->output_file != NULL)
				dup2(minishell->apps->fd_output_file, 1); // надо закрывать, если произошла ошибка исполнения программы?
			if (minishell->apps->input_file != NULL)
				dup2(minishell->apps->fd_input_file, 0); // если файл не найден, то запуска быть не должно; надо закрывать, если произошла ошибка исполнения программы?
			if (minishell->apps->heredoc != NULL)
				dup2(minishell->apps->fd[0], 0);
			execve(get_prog_name(minishell), minishell->apps->argv, get_arr_env(minishell->environment));
			executing_error(minishell);
			// printf("Программа %s на сработала, ошибка %s\n", minishell->apps->argv[0], strerror(errno));
			exit(errno); // нужен ли errno? smells
		}
		waitpid(-1, NULL, 0); // ожидание окончания дочернего процесса
		if (minishell->apps->next == NULL)
			break;
		minishell->apps = minishell->apps->next;
	}
}