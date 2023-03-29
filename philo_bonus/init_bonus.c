/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:29:50 by smiro             #+#    #+#             */
/*   Updated: 2022/11/27 18:29:52 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	init_philo(t_table *table, int total)
{
	int	i;

	i = 0;
	while (i < total)
	{
		table->philo[i].philo_num = i + 1;
		table->philo[i].table = table;
		table->philo[i].last_eat = 0;
		i++;
	}
}

static int	init_semaphore(t_table *table)
{
	sem_unlink("/forks");
	sem_unlink("/writing");
	sem_unlink("/eat_check");
	table->forks = sem_open("/forks", O_CREAT, S_IRWXU, table->total_philo);
	table->writing = sem_open("/writing", O_CREAT, S_IRWXU, 1);
	table->eat_check = sem_open("/eat_check", O_CREAT, S_IRWXU, 1);
	if (table->forks <= 0 || table->writing <= 0 || table->eat_check <= 0)
		return (1);
	return (0);
}

int	init(t_table *table, int total, char **av)
{
	table->total_philo = atoi(av[1]);
	if (init_semaphore(table))
		return (exit_error(2));
	table->time_to_die = atoi(av[2]);
	table->time_to_eat = atoi(av[3]);
	table->time_to_sleep = atoi(av[4]);
	table->x_eat = 0;
	table->everyone_alive = 1;
	if (av[5])
		table->x_eat = atoi(av[5]);
	table->philo = (t_philo *)malloc(sizeof(t_philo) * total);
	if (!table->philo)
		return (exit_error(2));
	init_philo(table, table->total_philo);
	return (0);
}

int	ft_atoi(const char *n)
{
	int	m;
	int	b;
	int	i;

	i = 0;
	m = 1;
	b = 0;
	while (n[i] == ' ' || n[i] == '\f' || n[i] == '\n'
		|| n[i] == '\r' || n[i] == '\t' || n[i] == '\v')
		i++;
	if (n[i] == '+' || n[i] == '-')
	{
		if (n[i] == '-')
			m = -m;
		i++;
	}
	while (n[i] >= '0' && n[i] <= '9')
	{
		b = b * 10 + (n[i] - '0');
		i++;
	}
	return (b * m);
}
