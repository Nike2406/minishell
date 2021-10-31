/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:37:20 by prochell          #+#    #+#             */
/*   Updated: 2021/10/31 14:50:54 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cntrl_c(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	errno = 1;
	return ;
}

void	base_signal(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, cntrl_c);
	signal(SIGQUIT, SIG_IGN);
	return ;
}

void	input_eof(void)
{
	// write(2, "\n", 1);
	// rl_replace_line("exit\n", 0);
	printf("exit\n"); // костыль?
	// rl_on_new_line();
	exit(0);
}

