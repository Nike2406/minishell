/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_once.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 20:20:28 by prochell          #+#    #+#             */
/*   Updated: 2021/11/07 21:35:42 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_once(char *str, char ch)
{
	int		i;
	char	**new_str;

	i = 0;
	if (!str || !ch)
		return NULL;
	new_str = (char **)malloc(sizeof(char *) * 3);
	if (!new_str)
		return NULL;
	while (str[i])
	{
		if (str[i] == ch)
			break;
		i++;
	}
	new_str[0] = ft_substr(str, 0, i);
	new_str[1] = ft_substr(str, i + 1, ft_strlen(str));
	new_str[2] = NULL;
	return (new_str);
}
