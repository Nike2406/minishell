/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 18:26:48 by prochell          #+#    #+#             */
/*   Updated: 2021/10/25 21:30:38 by prochell         ###   ########.fr       */
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
	tmp = ft_lstlast_minishell(*lst);
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
	nel->prev = NULL;
	return (nel);
}

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

t_envp	*ft_lstfirst_minishell(t_envp *lst)
{
	t_envp	*tmp;

	tmp = lst;
	if (!lst)
		return (NULL);
	while (tmp->prev)
		tmp = tmp->prev;
	return (tmp);
}

t_envp	*ft_lstdelone_minishell(t_envp *lst)
{
	t_envp	*before;
	t_envp	*after;

	before = NULL;
	after = NULL;
	if (!lst)
		return NULL;
	before = lst->prev;
	after = lst->next;
	if (lst->prev)
		before->next = lst->next;
	if (lst->next)
		after->prev = lst->prev;
	free(lst);
	return (before);
}
