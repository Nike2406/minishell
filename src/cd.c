/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:37:01 by prochell          #+#    #+#             */
/*   Updated: 2021/09/15 15:41:39 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_pwd(t_shell *minishell, char *str)
{
	t_envp	*tmp;

	tmp = minishell->environment;
	while (tmp)
	{
		if (!ft_strncmp(str, tmp->key, 4))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	change_old_new_pwd(t_shell *minishell, char *str, char *key)
{
	t_envp	*tmp;

	tmp = minishell->environment;
	while (tmp)
	{
		if (!ft_strncmp(key, tmp->key, 7))
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
	change_old_new_pwd(minishell, find_pwd(minishell, "PWD"), "OLDPWD");
	change_old_new_pwd(minishell, str, "PWD");
	if (chdir(str) != 0)
	{
		ft_error_cd_no_file(CD_NO_FILE, str);
		return ;
	}
}

void	cd_swap(t_shell *minishell, char **str)
{
	int		i;
	char	*tmp;

	i = 1;
	while (str[i])
	{
		if (!ft_strncmp("-", str[i], 2))
		{
			tmp = find_pwd(minishell, "OLDPWD");
			change_old_new_pwd(minishell, find_pwd(minishell, "PWD"), "OLDPWD");
			change_old_new_pwd(minishell, tmp, "PWD");
		}
	i++;
	}
	return ;
}

int	get_cd(t_shell *minishell, char **str)
{
	char	*oldpwd;
	char	*newpwd;

	if (!ft_strncmp("cd", str[0], 3))
	{
		if (!str[1] || !ft_strncmp("~", str[1], 2))
		{
			cd_get_home(minishell);
			return (0);
		}
		oldpwd = getcwd(NULL, 0);
		if (oldpwd == NULL)
			return (ft_error_cd(CD_CWD));
		if (!ft_strncmp("-", str[1], 2))
		{
			cd_swap(minishell, str);
			return (0);
		}
		if (chdir(str[1]) != 0)
			return (ft_error_cd_no_file(CD_NO_FILE, str[1]));
		newpwd = getcwd(NULL, 0);
		if (newpwd == NULL)
			return (ft_error_cd(CD_CWD));
		change_old_new_pwd(minishell, oldpwd, "OLDPWD");
		change_old_new_pwd(minishell, newpwd, "PWD");
		return (0);
	}
	return (1);
}
