/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:06:41 by smiro             #+#    #+#             */
/*   Updated: 2022/11/27 19:06:43 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	check_death(t_table *table, t_philo *philo)
{
	int	i;

	usleep(100);
	while (1)
	{
		i = 0;
		while (i < table->total_philo)
		{
			while (table->x_eat && philo[i].times_ate == table->x_eat)
			{
				i++;
				if (i == table->total_philo)
					return ;
			}
			pthread_mutex_lock(&table->meal_check);
			if (philo[i].last_eat + table->time_to_die < get_time())
				state(philo, DIE);
			pthread_mutex_unlock(&table->meal_check);
			usleep(100);
			i++;
		}
	}
}

static void	philo_eats(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&table->philo[philo->left_index].fork);
	state(philo, FORK);
	pthread_mutex_lock(&table->philo[philo->rigth_index].fork);
	state(philo, FORK);
	pthread_mutex_lock(&table->meal_check);
	philo->last_eat = get_time();
	state(philo, EAT);
	pthread_mutex_unlock(&table->meal_check);
	ft_sleep(table->time_to_eat);
	pthread_mutex_unlock(&table->philo[philo->left_index].fork);
	pthread_mutex_unlock(&table->philo[philo->rigth_index].fork);
	(philo->times_ate)++;
}

static void	*action(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	philo->last_eat = get_time();
	while (1)
	{
		state(philo, THINK);
		philo_eats(philo, table);
		if (table->x_eat && philo->times_ate == table->x_eat)
			break ;
		state(philo, SLEEP);
		ft_sleep(table->time_to_sleep);
	}
	return (NULL);
}

int	start_simulation(t_table *table)
{
	int			i;
	pthread_t	*th;

	th = (pthread_t *)malloc(sizeof(pthread_t) * table->total_philo);
	if (!th)
		return (exit_error(2));
	i = 0;
	while (i < table->total_philo)
	{
		pthread_create(&th[i], NULL,
			(void *(*)(void *))action, &table->philo[i]);
		i++;
	}
	check_death(table, table->philo);
	while (i-- > 0)
		pthread_join(th[i], NULL);
	free(th);
	return (0);
}
