/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 15:32:59 by smiro             #+#    #+#             */
/*   Updated: 2022/11/26 15:33:00 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	state(t_philo *philo, int n)
{
	int			temp;
	
	pthread_mutex_lock(&philo->table->writing);
	if (n == 0)
		temp = printf("%lld %d has taken a fork %d %d\n", time_diff(philo->table->start, get_time()), philo->philo_num, philo->left_index, philo->rigth_index);
	if (n == 1)
		temp = printf("%lld %d is eating\n", time_diff(philo->table->start, get_time()), philo->philo_num);
	if (n == 2)
		temp = printf("%lld %d is sleeping\n", time_diff(philo->table->start, get_time()), philo->philo_num);
	if (n == 3)
		temp = printf("%lld %d is thinking\n", time_diff(philo->table->start, get_time()), philo->philo_num);
	if (n == 4)
	{
		temp = printf("%lld %d died\n", time_diff(philo->table->start, get_time()), philo->philo_num);
		exit(DIE);
	}
	if (temp == -1)
		exit(1);
	pthread_mutex_unlock(&philo->table->writing);
}

void	init(t_table *table, int total, char **av)
{
	int	i;
	
	i = 0;
	table->start = get_time();
	pthread_mutex_init(&table->writing, NULL);
	table->time_to_die = atoi(av[2]);
	table->time_to_eat = atoi(av[3]);
	table->time_to_sleep = atoi(av[4]);
	table->x_eat = 0;
	if (av[5])
		table->x_eat = atoi(av[5]);
	while (i < total)
	{
		pthread_mutex_init(&table->philo[i].fork, NULL);
		table->philo[i].philo_num = i + 1;
		table->philo[i].left_index = (i - 1);
		table->philo[i].rigth_index = i + 1;
		table->philo[i].table = table;
		i++;
	}
	table->philo[0].left_index = total - 1;
	table->philo[total - 1].rigth_index = 0;
}

long long	time_diff(long long past, long long current)
{
	return (current - past);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}