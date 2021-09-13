/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:37:01 by prochell          #+#    #+#             */
/*   Updated: 2021/09/13 15:45:09 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	check_pwd(t_shell *minishell)
// {
// 	// Check env
// 	t_envp	*env_tmp;
// 	env_tmp = minishell->environment;
// 	while (env_tmp != NULL)
// 	{
// 		printf("key = %s, value = %s\n", env_tmp->key, env_tmp->value);
// 		env_tmp = env_tmp->next;
// 	}
// 	// End
// }

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
		{
			printf("str = %s ", str);
			printf("key = %s\n", tmp->key);
			tmp->value = str;
			return ;
		}
		tmp = tmp->next;
	}
}
void	change_newpwd(t_shell *minishell, char *str)
{
	t_envp	*tmp;

	tmp = minishell->environment;
	while (tmp)
	{
		if (!ft_strncmp("PWD", tmp->key, 4))
		{
			tmp->value = str;
			return ;
		}
		tmp = tmp->next;
	}
}

void	cd_get_home(t_shell *minishell)
{
	t_envp	*tmp;
	char	*str;

	tmp = minishell->environment;
	while (tmp)
	{
		if (!ft_strncmp("HOME", tmp->key, 5))
			str = tmp->value;
		tmp = tmp->next;
	}
	change_oldpwd(minishell, find_pwd(minishell));
	change_newpwd(minishell, str);
	if (chdir(str) != 0)
	{
		ft_error_cd_no_file(CD_NO_FILE, str);
		return ;
	}
}

// int	parse_cd(char **str)
// {
// 	int	i;
// 	int	j;
// 	char	**tmp;

// 	i = 0;
// 	j = 0;
// 	tmp = ft_split(str[1], '/');
// 	while (tmp[i])
// 	{
// 		if (!ft_strncmp(tmp[i], "..", 3))
// 			j++;
// 		else
// 			ft_error_cd(CD_NO_FILE);
// 		i++;
// 	}
// 	return (i);
// }

int	get_cd(t_shell *minishell, char **str)
{
	char	*oldpwd;
	char	*newpwd;
	// char	*tmp;
	// (void)minishell;

	if (!ft_strncmp("cd", str[0], 3))
	{
		// parse_cd(str);
		// if (!str[1])
		// 	return (1);
		if (!str[1] || !ft_strncmp("~", str[1], 2))
		{
			cd_get_home(minishell);
			return (0);
		}

		// check
		// if (!ft_strncmp("env", str[1], 4))
		// {
		// 	check_pwd(minishell);
		// 	return (0);
		// }

		// oldpwd = find_pwd(minishell);
		oldpwd = getcwd(NULL, 0);
		if (oldpwd == NULL)
			return (ft_error_cd(CD_CWD));
		if (chdir(str[1]) != 0)
			return (ft_error_cd_no_file(CD_NO_FILE, str[1]));

		// tmp = malloc(ft_strlen(oldpwd) + 1024);
		// if (!tmp)
		// 	return (1);
		printf("old = %s\n", oldpwd);
		newpwd = getcwd(NULL, 0);// find_pwd(minishell);
		if (newpwd == NULL)
			return (ft_error_cd(CD_CWD));
		// free(tmp);
		printf("new = %s\n", newpwd);
		change_oldpwd(minishell, oldpwd);
		change_newpwd(minishell, newpwd);

		// printf("%s\n", oldpwd);
		// change_oldpwd(minishell, oldpwd);
		// printf("%s\n", tmp);
		// printf("HI here is: %s\n", oldpwd);
		// change_oldpwd(minishell, oldpwd);
		// execlp("env", "env", NULL);

		return (0);
	}
	return (1);
}
