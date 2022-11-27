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

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_philo
{
	int				philo_num;
	int				left_index;
	int				rigth_index;
	long long		last_eat;
	int				times_ate;
	pthread_mutex_t	fork;
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
	t_philo			*philo;
	pthread_mutex_t	writing;
	pthread_mutex_t	meal_check;
}							t_table;

void		state(t_philo *philo, int n);
int			init(t_table *table, int total, char **av);
long long	get_time(void);
long long	time_diff(long long past, long long current);
void		ft_sleep(long long time);
int			exit_error(int error);
int			free_n_destroy(t_table *table);
int			start_simulation(t_table *table);

# define FORK 0
# define EAT	1
# define SLEEP 2
# define THINK 3
# define DIE 4

#endif
