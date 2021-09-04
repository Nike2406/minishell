/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 18:26:48 by prochell          #+#    #+#             */
/*   Updated: 2021/09/04 18:55:39 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_minishell(t_envp **lst, t_envp *new)
{
	t_envp	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = ft_lstlast_ps(*lst);
	new->prev = tmp;
	tmp->next = new;
}

void	ft_lstclear_minishell(t_envp **lst)
{
	t_envp	*tmp;

	tmp = NULL;
	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
}

t_envp	*ft_lstlast_minishell(t_envp *lst)
{
	t_envp	*tmp;

	tmp = lst;
	if (!lst)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_envp	*ft_lstnew_minishell(char *key, char *value)
{
	t_envp	*nel;

	nel = (t_envp *)malloc(sizeof(t_envp));
	if (!nel)
		return (NULL);
	nel->key = key;
	nel->value = value;
	nel->next = NULL;
	return (nel);
}

int	ft_lstsize_ps(t_envp *lst)
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
