/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:37:01 by prochell          #+#    #+#             */
/*   Updated: 2021/11/12 17:53:02 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_pwd(t_shell *minishell, char *str)
{
	t_envp	*tmp;

	tmp = minishell->environment;
	while (tmp)
	{
		if (!ft_strcmp(str, tmp->key))
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
		if (!ft_strcmp(key, tmp->key))
		{
			tmp->value = str;
			return ;
		}
		tmp = tmp->next;
	}
}

static int	cd_get_home(t_shell *minishell)
{
	t_envp	*tmp;
	char	*str;

	tmp = minishell->environment;
	while (tmp)
	{
		if (!ft_strcmp("HOME", tmp->key))
			str = tmp->value;
		tmp = tmp->next;
	}
	if (!tmp)
		return (ft_error_cd_home_not_set(minishell));
	change_old_new_pwd(minishell, find_pwd(minishell, "PWD"), "OLDPWD");
	change_old_new_pwd(minishell, str, "PWD");
	if (chdir(str) != 0)
		ft_error_cd_no_file(minishell, str);
	else
		minishell->child_exit_status = 0;
	return (0);
}

int	cd_swap(t_shell *minishell, char **str)
{
	int		i;
	char	*tmp;

	i = 1;
	while (str[i])
	{
		if (!ft_strcmp("-", str[i]))
		{
			tmp = find_pwd(minishell, "OLDPWD");
			change_old_new_pwd(minishell, find_pwd(minishell, "PWD"), "OLDPWD");
			change_old_new_pwd(minishell, tmp, "PWD");
			if (chdir(tmp) != 0)
				return (ft_error_cd_no_file(minishell, tmp));
		}
		i++;
	}
	minishell->child_exit_status = 0;
	return (0);
}

int	get_cd(t_shell *minishell, char **str)
{
	char	*oldpwd;
	char	*newpwd;

	if (!ft_strcmp("cd", str[0]))
	{
		if (!str[1] || !ft_strcmp("~", str[1]))
			return (cd_get_home(minishell));
		oldpwd = getcwd(NULL, 0);
		if (oldpwd == NULL)
			return (ft_error_cd(minishell));
		if (!ft_strncmp("-", str[1], 2))
			return (cd_swap(minishell, str));
		if (chdir(str[1]) != 0)
			return (ft_error_cd_no_file(minishell, str[1]));
		newpwd = getcwd(NULL, 0);
		if (newpwd == NULL)
			return (ft_error_cd(minishell));
		change_old_new_pwd(minishell, oldpwd, "OLDPWD");
		change_old_new_pwd(minishell, newpwd, "PWD");
		minishell->child_exit_status = 0;
		return (0);
	}
	return (1);
}
