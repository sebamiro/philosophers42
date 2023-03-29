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

#include "philo_bonus.h"

static void	*check_death(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	while (table->everyone_alive)
	{
		sem_wait(table->eat_check);
		if (time_diff(philo->last_eat, get_time()) >= table->time_to_die)
		{
			state(philo, DIE);
			table->everyone_alive = 0;
			sem_wait(table->writing);
			exit(1);
		}
		sem_post(table->eat_check);
		usleep(1000);
		if (!(table->everyone_alive))
			break ;
		if (table->x_eat && philo->times_ate == table->x_eat)
			break ;
	}
	return (NULL);
}

static void	philo_eats(t_philo *philo, t_table *table)
{
	sem_wait(table->forks);
	state(philo, FORK);
	sem_wait(table->forks);
	state(philo, FORK);
	sem_wait(table->eat_check);
	state(philo, EAT);
	(philo->times_ate)++;
	philo->last_eat = get_time();
	sem_post(table->eat_check);
	ft_sleep(table->time_to_eat);
	sem_post(table->forks);
	sem_post(table->forks);
}

static void	action(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	philo->last_eat = get_time();
	pthread_create(&(philo->th), NULL, (void *(*)(void *))check_death, philo);
	while (table->everyone_alive)
	{
		philo_eats(philo, table);
		if ((table->x_eat && philo->times_ate == table->x_eat))
			break ;
		state(philo, SLEEP);
		ft_sleep(table->time_to_sleep);
		state(philo, THINK);
	}
	pthread_join(philo->th, NULL);
	if (!table->everyone_alive)
		exit(1);
	exit(0);
}

void	exit_simulation(t_table *table)
{
	int	status;
	int	i;

	i = 0;
	while (i < table->total_philo)
	{
		waitpid(-1, &status, 0);
		if (status)
		{
			i = -1;
			while (++i < table->total_philo)
				kill(table->philo[i].pid, SIGTERM);
			break ;
		}
		i++;
	}
	sem_close(table->forks);
	sem_close(table->writing);
	sem_close(table->eat_check);
	sem_unlink("/forks");
	sem_unlink("/writing");
	sem_unlink("/eat_check");
}

int	start_simulation(t_table *table)
{
	int			i;

	i = -1;
	table->start = get_time();
	while (++i < table->total_philo)
	{
		table->philo[i].pid = fork();
		if (table->philo[i].pid < 0)
			return (1);
		if (table->philo[i].pid == 0)
			action(&(table->philo[i]));
		usleep(50);
	}
	exit_simulation(table);
	return (0);
}
