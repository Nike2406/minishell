#include "minishell.h"

char	*get_prog_name(t_shell *minishell)
{
	int				i;
	DIR				*dir;
	struct dirent	*tmp;
	char			*ret;
	char			**paths;

	paths = ft_split(getenv("PATH"), ':'); // заменить на свой env!!!!
	i = 0;
	while (paths[i])
	{
		dir = opendir(paths[i]);
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
		i++;
	}
	return (minishell->apps->argv[0]);
}

void	minishell_executor(t_shell *minishell)
{
	pid_t	pid;
	pid = fork();
	if (pid == 0)
	{
		//printf("%s\n", minishell->apps->argv[0]);
		execve(get_prog_name(minishell), minishell->apps->argv, minishell->envp);
		perror("lol"); // проверка, если екзекве не сработал, иные действия
		//printf("%d\n", errno);
		exit(errno); // нужен ли?
	}
	wait(NULL); // ожидание окончания дочернего процесса

}