/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:37:01 by prochell          #+#    #+#             */
/*   Updated: 2021/09/08 20:28:39 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_pwd(t_shell *minishell)
{
	// Check env
	t_envp	*env_tmp;
	env_tmp = minishell->environment;
	while (env_tmp != NULL)
	{
		printf("key = %s, value = %s\n", env_tmp->key, env_tmp->value);
		env_tmp = env_tmp->next;
	}
	// End
}

char	*find_pwd(t_shell *minishell)
{
	t_envp	*tmp;

	tmp = minishell->environment;
	while (tmp)
	{
		if (!ft_strncmp("PWD", tmp->key, 4))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	change_oldpwd(t_shell *minishell, char *str)
{
	t_envp	*tmp;

	tmp = minishell->environment;
	while (tmp)
	{
		if (!ft_strncmp("OLDPWD", tmp->key, 7))
			tmp->value = str;
		tmp = tmp->next;
	}
}

int	parse_cd(char **str)
{
	int	i;
	int	j;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = ft_split(str[1], '/');
	while (tmp[i])
	{
		if (!ft_strncmp(tmp[i], "..", 3))
			j++;
		else
			ft_error_cd(CD_NO_FILE);
		i++;
	}
	return (i);
}

int	get_cd(t_shell *minishell, char **str)
{
	char	*oldpwd;
	char	tmp[256];

	if (!ft_strncmp("cd", str[0], 3))
	{
		// parse_cd(str);
		chdir("/Users/prochell/projects");

		oldpwd = getcwd(tmp, sizeof(tmp));// find_pwd(minishell);
		change_oldpwd(minishell, oldpwd);
		// printf("HI here is: %s\n", oldpwd);
		// change_oldpwd(minishell, oldpwd);
		execlp("env", "env", NULL);
		// check_pwd(minishell);
		return (0);
	}
	return (1);
}
