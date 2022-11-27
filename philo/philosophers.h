/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 15:26:04 by smiro             #+#    #+#             */
/*   Updated: 2022/11/26 15:26:05 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_philo
{
	int	philo_num;
	int	left_index;
	int	rigth_index;
	int	times_ate;
	pthread_mutex_t	fork;
	struct s_table	*table;
}							t_philo;

typedef struct s_table
{
	long long	start;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	x_eat;
	t_philo	*philo;
	pthread_mutex_t writing;
}							t_table;

void	state(t_philo *philo, int n);
void	init(t_table *table, int total, char **av);
long long	get_time(void);
long long	time_diff(long long past, long long current);

# define FORK 0
# define EAT	1
# define SLEEP 2
# define THINK 3
# define DIE 4

#endif