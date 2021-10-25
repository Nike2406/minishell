/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 18:22:26 by prochell          #+#    #+#             */
/*   Updated: 2021/10/25 21:30:38 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_check_flag(char *str)
{
	int	j;

	j = 2;
	if (str[0] == '-' && str[1] == 'n')
	{
		if (!str[j + 1])
			return (1);
		while (str[j])
		{
			if (str[j] != 'n')
				return (0);
			else
				if (!str[j + 1])
					return (1);
			j++;
		}
	}
	return (0);
}

void	write_echo(char **args, int i, int n)
{
	while (args[i])
	{
		ft_putstr(args[i]);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n)
		ft_putstr("\n");
}

int	get_echo(char **args)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (!ft_strncmp("echo", args[0], 5))
	{
		if (args[1] == NULL)
			return (1);
		while (args[i])
		{
			if (echo_check_flag(args[i]))
				n++;
			else
				break;
			if (n)
				i++;
		}
		write_echo(args, i, n);
		return (0);
	}
	return (1);
}
