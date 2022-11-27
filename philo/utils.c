/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:03:12 by smiro             #+#    #+#             */
/*   Updated: 2022/11/27 18:03:15 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	state(t_philo *philo, int n)
{
	int			temp;

	pthread_mutex_lock(&philo->table->writing);
	if (n == 0)
		temp = printf("%lld %d has taken a fork\n",
				time_diff(philo->table->start, get_time()), philo->philo_num);
	if (n == 1)
		temp = printf("%lld %d is eating\n",
				time_diff(philo->table->start, get_time()), philo->philo_num);
	if (n == 2)
		temp = printf("%lld %d is sleeping\n",
				time_diff(philo->table->start, get_time()), philo->philo_num);
	if (n == 3)
		temp = printf("%lld %d is thinking\n",
				time_diff(philo->table->start, get_time()), philo->philo_num);
	if (n == 4)
	{
		temp = printf("%lld %d died\n",
				time_diff(philo->table->start, get_time()), philo->philo_num);
		exit(DIE);
	}
	if (temp == -1)
		exit(1);
	pthread_mutex_unlock(&philo->table->writing);
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

void	ft_sleep(long long time)
{
	long long	current;

	current = get_time();
	while (1)
	{
		if (time_diff(current, get_time()) >= time)
			break ;
		usleep(50);
	}
}
