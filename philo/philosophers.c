/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 15:45:16 by smiro             #+#    #+#             */
/*   Updated: 2022/11/26 15:45:19 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*action(t_philo *philo)
{
	long long last_eat;
	t_table	*table;

	table = philo->table;
	last_eat = get_time();
	while (1)
	{
		state(philo, THINK);
		pthread_mutex_lock(&table->philo[philo->left_index].fork);
		state(philo, FORK);
		pthread_mutex_lock(&table->philo[philo->rigth_index].fork);
		state(philo, FORK);
		if (last_eat + table->time_to_die < get_time())
			state(philo, DIE);
		state(philo, EAT);
		usleep(table->time_to_eat * 1000);
		(philo->times_ate)++;
		pthread_mutex_unlock(&table->philo[philo->left_index].fork);
		pthread_mutex_unlock(&table->philo[philo->rigth_index].fork);
		if (table->x_eat && philo->times_ate == table->x_eat)
			break ;
		last_eat = get_time();
		state(philo, SLEEP);
		usleep(table->time_to_sleep * 1000);
	}
	return (NULL);
}

int	main(int	ac, char **av)
{
	t_table	*table;
	pthread_t *th;
	int	i;
	int	total;
	
	i = 0;
	if (ac < 5 || ac > 6)
		return (1);
	total = atoi(av[1]);
	table = (t_table *)malloc(sizeof(t_table));
	table->philo = (t_philo *)malloc(sizeof(t_philo) * total);
	if (!table->philo)
		return (2);
	th = (pthread_t *)malloc(sizeof(pthread_t) * total);
	init(table, total, av);
	while (i < total)
	{
		pthread_create(&th[i], NULL, (void *(*)(void *))action, (void *)&table->philo[i]);
		i++;
	}
	while (i-- > 0)
	{
		pthread_mutex_destroy(&table->philo[i].fork);
		pthread_join(th[i], NULL);
	}
}
