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

#include "philo_bonus.h"

void	state(t_philo *philo, int n)
{
	int			temp;

	sem_wait(philo->table->writing);
	if (n == 0 && philo->table->everyone_alive)
		temp = printf("%lld %d has taken a fork\n",
				time_diff(philo->table->start, get_time()), philo->philo_num);
	if (n == 1 && philo->table->everyone_alive)
		temp = printf("%lld %d is eating\n",
				time_diff(philo->table->start, get_time()), philo->philo_num);
	if (n == 2 && philo->table->everyone_alive)
		temp = printf("%lld %d is sleeping\n",
				time_diff(philo->table->start, get_time()), philo->philo_num);
	if (n == 3 && philo->table->everyone_alive)
		temp = printf("%lld %d is thinking\n",
				time_diff(philo->table->start, get_time()), philo->philo_num);
	if (n == 4 && philo->table->everyone_alive)
		temp = printf("%lld %d died\n",
				time_diff(philo->table->start, get_time()), philo->philo_num);
	if (temp == -1 && philo->table->everyone_alive)
		return ;
	sem_post(philo->table->writing);
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
		usleep(100);
	}
}

int	ft_check(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ac < 5 || ac > 6)
		return (1);
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9'
				|| (i == 5 && av[i][0] == '0'))
				return (1);
			j++;
		}
		if (j >= 10)
			return (1);
		i++;
	}
	return (0);
}
