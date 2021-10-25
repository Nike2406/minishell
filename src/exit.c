/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:56:00 by prochell          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/10/12 20:11:30 by prochell         ###   ########.fr       */
=======
/*   Updated: 2021/10/17 19:21:52 by prochell         ###   ########.fr       */
>>>>>>> prochell
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_exit(t_shell *minishell, char **str)
{
	(void)minishell;
	(void)str;
	if (!ft_strncmp("exit", str[0], 5))
	{
		exit(0);
	}
	return (1);
}
