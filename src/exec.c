/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 21:45:22 by prochell          #+#    #+#             */
/*   Updated: 2021/10/14 22:45:22 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (acss == -1)
		printf("Wrong command!\n");
	return NULL;
}

int	get_exec(t_shell *minishell, char **str)
{
	char	**path;
	char	*cmd;
	int		exec;

	path = get_path(minishell->environment);
	cmd = chk_cmd(path, str[0]);

	// ЗАпилить через форки!
	exec = execve(cmd, str, NULL);
	if (exec < 0)
		printf("Wrong command!\n");
	// int i = -1;
	// while (path[++i])
	// 	printf("%s\n", path[i]);
	return (0);
}