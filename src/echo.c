/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 18:22:26 by prochell          #+#    #+#             */
/*   Updated: 2021/09/07 15:07:48 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_echo(char **args)
{
	int	i;
	int	n;

	n = 0;
	i = 1;
	if (!ft_strncmp("echo", args[0], 6))
	{
		if (args[1] == NULL)
			return (1);
		if (!ft_strncmp("-n", args[1], 3))
		{
			n = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr(args[i]);
			if (args[i + 1])
				write(1, " ", 1);
			i++;
		}
		if (!n)
			ft_putstr("\n");
		free(args);
		return (0);
	}
	return (1);
}
