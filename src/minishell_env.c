/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 00:04:48 by prochell          #+#    #+#             */
/*   Updated: 2021/11/09 20:58:00 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_environment(t_shell *minishell, char **env)
{
	char	**tmp;
	int		i;

	i = 0;
	while (env[i])
	{
		tmp = ft_split(env[i], '=');
		ft_lstadd_back_minishell(&minishell->environment,
			ft_lstnew_minishell(tmp[0], tmp[1]));
		i++;
		free(tmp);
	}
}

int	get_env(t_shell *minishell, char **str)
{
	t_envp	*env_tmp;

	if (!ft_strcmp("env", str[0]))
	{
		env_tmp = minishell->environment;
		while (env_tmp != NULL)
		{
			printf("%s=%s\n", env_tmp->key, env_tmp->value);
			env_tmp = env_tmp->next;
		}
		minishell->child_exit_status = 0;
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