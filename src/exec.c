/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 21:45:22 by prochell          #+#    #+#             */
/*   Updated: 2021/10/15 16:44:50 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

char	**get_path(t_envp *env)
{
	int		i;
	char	**addr;
	char	*tmp_str;
	t_envp	*tmp;

	tmp = env;
	while(tmp)
	{
		if (ft_strnstr(tmp->key, "PATH", 5))
			break ;
		tmp = tmp->next;
	}
	addr = ft_split(tmp->value, ':');
	i = -1;
	while (addr[++i])
	{
		tmp_str = addr[i];
		addr[i] = ft_strjoin(addr[i], "/");
		free(tmp_str);
	}
	return (addr);
}

char	*chk_cmd(char **addr, char *cmd)
{
	int		i;
	int		acss;
	char	*tmp_cmd;

	i = 0;
	acss = 0;
	while (addr[i])
	{
		tmp_cmd = ft_strjoin(addr[i], cmd);
		acss = access(tmp_cmd, 1);
		if (acss >= 0)
			return tmp_cmd;
		i++;
		free(tmp_cmd);
	}
	// if (acss == -1)
	// 	exit (0);
	return NULL;
}

int	get_exec(t_shell *minishell, char **str)
{
	char	**path;
	char	*cmd;
	int		exec;
	int		pid;

	pid = fork();
	if (pid < 0)
	{
		printf("Fork error!\n");
		return (1);
	}
	if (!pid)
	{
		path = get_path(minishell->environment);
		cmd = chk_cmd(path, str[0]);
		path = get_arr_env(minishell->environment);

		int j = 0;
		printf("!!!!\n");
		printf("%s\n", path[0]);
		while (path[j])
		{
			printf("%s", path[j]);
			j++;
		}

		exec = execve(cmd, str, NULL); // двумерный массив envp
		if (exec < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(str[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			// printf("minishell: %s: command not found\n", str[0]);
			exit (1);
		}
	}
	else
		wait(NULL);
	return (0);
}