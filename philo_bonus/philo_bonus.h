/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:03:03 by smiro             #+#    #+#             */
/*   Updated: 2022/11/27 18:03:06 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philo
{
	int				pid;
	int				philo_num;
	long long		last_eat;
	int				times_ate;
	pthread_t		th;
	struct s_table	*table;
}							t_philo;

typedef struct s_table
{
	int				total_philo;
	long long		start;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				x_eat;
	int				everyone_alive;
	sem_t			*forks;
	sem_t			*writing;
	sem_t			*eat_check;
	t_philo			*philo;
}							t_table;

void		state(t_philo *philo, int n);
int			init(t_table *table, int total, char **av);
long long	get_time(void);
long long	time_diff(long long past, long long current);
void		ft_sleep(long long time);
int			exit_error(int error);
int			free_n_destroy(t_table *table);
int			start_simulation(t_table *table);
int			ft_atoi(const char *n);
int			ft_check(int ac, char **av);

# define FORK 0
# define EAT	1
# define SLEEP 2
# define THINK 3
# define DIE 4

#endif
