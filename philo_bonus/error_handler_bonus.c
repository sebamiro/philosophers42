/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:43:00 by smiro             #+#    #+#             */
/*   Updated: 2022/11/27 18:43:02 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	free_n_destroy(t_table *table)
{
	if (table->philo)
		free(table->philo);
	free(table);
	return (0);
}

static int	write_error(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (write(2, str, len));
}

int	exit_error(int error)
{
	if (error == 1)
		return (write_error("Wrong argument\n"));
	if (error == 2)
		return (write_error("Fatal error when allocating memory\n"));
	return (0);
}
