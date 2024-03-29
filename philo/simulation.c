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

static void	check_death(t_philo *philo)
{
	int		i;
	t_table	*table;

	table = philo->table;
	while (table->everyone_alive)
	{
		i = -1;
		while (++i < table->total_philo && table->everyone_alive)
		{
			pthread_mutex_lock(&table->eat_check);
			if (time_diff(philo[i].last_eat, get_time()) >= table->time_to_die)
			{
				state(&philo[i], DIE);
				table->everyone_alive = 0;
			}
			pthread_mutex_unlock(&table->eat_check);
			usleep(50);
		}
		if (!(table->everyone_alive))
			break ;
		i = -1;
		while (table->x_eat && philo[++i].times_ate == table->x_eat)
			if (i == table->total_philo)
				return ;
	}
}

static void	philo_eats(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&table->philo[philo->left_index].fork);
	state(philo, FORK);
	pthread_mutex_lock(&table->philo[philo->rigth_index].fork);
	state(philo, FORK);
	pthread_mutex_lock(&table->eat_check);
	state(philo, EAT);
	(philo->times_ate)++;
	philo->last_eat = get_time();
	pthread_mutex_unlock(&table->eat_check);
	ft_sleep(table->time_to_eat);
	pthread_mutex_unlock(&table->philo[philo->left_index].fork);
	pthread_mutex_unlock(&table->philo[philo->rigth_index].fork);
}

static void	*action(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (philo->philo_num % 2)
		usleep(1500);
	while (table->everyone_alive)
	{
		philo_eats(philo, table);
		if ((table->x_eat && philo->times_ate == table->x_eat)
			|| !(table->everyone_alive))
			break ;
		state(philo, SLEEP);
		ft_sleep(table->time_to_sleep);
		state(philo, THINK);
	}
	return (NULL);
}

int	start_simulation(t_table *table)
{
	int			i;
	pthread_t	*th;

	th = (pthread_t *)malloc(sizeof(pthread_t) * table->total_philo);
	if (!th)
		return (2);
	i = 0;
	while (i < table->total_philo)
	{
		if (pthread_create(&th[i], NULL,
				(void *(*)(void *))action, &table->philo[i]))
			return (3);
		table->philo[i].last_eat = get_time();
		i++;
	}
	check_death(table->philo);
	while (--i > 0)
		if (pthread_join(th[i], NULL))
			return (4);
	if (th)
		free(th);
	return (0);
}
