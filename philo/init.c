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

#include "philosophers.h"

static void	init_philo(t_table *table, int total)
{
	int	i;

	i = 0;
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

int	init(t_table *table, int total, char **av)
{
	table->start = get_time();
	table->total_philo = atoi(av[1]);
	pthread_mutex_init(&table->writing, NULL);
	pthread_mutex_init(&table->meal_check, NULL);
	table->time_to_die = atoi(av[2]);
	table->time_to_eat = atoi(av[3]);
	table->time_to_sleep = atoi(av[4]);
	table->x_eat = 0;
	if (av[5])
		table->x_eat = atoi(av[5]);
	table->philo = (t_philo *)malloc(sizeof(t_philo) * total);
	if (!table->philo)
		return (exit_error(2));
	init_philo(table, table->total_philo);
	return (0);
}
