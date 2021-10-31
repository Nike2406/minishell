/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:45:59 by signacia          #+#    #+#             */
/*   Updated: 2021/10/31 10:15:34 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sighandler(int sig)
{
	(void)sig;
	printf("\b\br\n");
	printf("\e[0;32mminishell$\e[0;39m ");
}