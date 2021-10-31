/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 00:04:48 by prochell          #+#    #+#             */
/*   Updated: 2021/10/31 18:45:45 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_environment(char **env, t_shell *minishell)
{
	char	**tmp;
	int		i;
	// int j = 0;

	i = 0;
	// char	*tmp2;
	while (env[i])
	{
		tmp = ft_split(env[i], '=');
		// tmp2 = malloc(ft_strlen(tmp[1]));
		// while (tmp[1][j] != '\n')
		// {
		// 	tmp2[j] = tmp[1][j];
		// 	j++;
		// }
		ft_lstadd_back_minishell(&minishell->environment, \
			ft_lstnew_minishell(tmp[0], tmp[1]));
		i++;
		free(tmp);
	}
}

int	get_env(t_shell *minishell, char **str)
{
	if (!ft_strcmp("env", str[0]))
	{
		t_envp	*env_tmp;
		env_tmp = minishell->environment;
		while (env_tmp != NULL)
		{
			printf("%s=%s\n", env_tmp->key, env_tmp->value);
			env_tmp = env_tmp->next;
		}
		return (0);
	}
	return (1);
}

char	*ft_getenv_value(t_envp *lst, char *key)
{
	t_envp	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (!ft_strcmp(key, tmp->key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return ("");
}
