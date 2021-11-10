/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:40:10 by signacia          #+#    #+#             */
/*   Updated: 2021/11/10 18:40:11 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr(char *a)
{
	int	i;

	if (!a)
		return ;
	i = 0;
	while (a[i])
	{
		write(1, &a[i], 1);
		i++;
	}
}
