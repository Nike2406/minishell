/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:25:47 by signacia          #+#    #+#             */
/*   Updated: 2021/11/10 18:31:52 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize(t_envp *lst)
{
	unsigned int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	check_list(t_envp *list)
{
	t_envp	*tmp_lst;

	tmp_lst = list;
	while (tmp_lst)
	{
		printf("declare -x %s=\"%s\"\n", tmp_lst->key, tmp_lst->value);
		tmp_lst = tmp_lst->next;
	}
}

char	**get_arr_env(t_envp *env)
{
	t_envp	*tmp_env;
	char	**arr;
	char	*tmp;
	int		i;

	tmp_env = env;
	i = ft_lstsize(tmp_env);
	arr = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (tmp_env)
	{
		tmp = ft_strjoin(tmp_env->key, "=");
		arr[i] = ft_strjoin(tmp, tmp_env->value);
		free(tmp);
		tmp_env = tmp_env->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
