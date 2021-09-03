/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prochell <prochell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 14:52:46 by prochell          #+#    #+#             */
/*   Updated: 2021/08/24 23:43:24 by prochell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

# define T_L_FORK	1
# define T_R_FORK	2
# define EATING		3
# define SLEEPING	4
# define THINKING	5
# define DEATH		6

typedef pthread_mutex_t	t_forks;
typedef struct s_data
{
	int		num_of_ph;
	int		t_to_die;
	int		t_to_eat;
	int		t_to_sleep;
	int		ph_m_to_eat;
	int		time;
	int		flag_eating_tms;
	t_forks	*mutex;
}	t_data;

typedef struct s_philo
{
	int		id;
	t_forks	*left_fork;
	t_forks	*right_fork;
	t_data	*data;
	int		status;
	int		hungry_time;
	int		eat_count;
	int		is_full;
}	t_philo;

int		p_err(int err);
int		p_limits(long long total, char const s, int sign);
int		p_atoi(const char *str);
int		check_nums(char **args);
int		get_time(void);
void	p_usleep(long long time);

int		data_fill(int argc, char **argv, t_data *data);
int		philo_phill(t_data *philo);
void	*philo_action(void *data);
void	philo_messages(int i, int a, int b, t_forks *mutex);
void	philo_destroy(t_philo **phils, t_data *data);

int		waitress(t_philo **phils);
void	*check_philo(void *phils);
int		check_fullfillment(t_philo **tmp);

void	take_forks(t_philo *philo);
int		eating(t_philo *philo);
void	sleeping(t_philo *philo);

#endif
