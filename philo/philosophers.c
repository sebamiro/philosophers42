/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:02:55 by smiro             #+#    #+#             */
/*   Updated: 2022/11/27 18:02:59 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_table	*table;

	if (ac < 5 || ac > 6)
		return (exit_error(1));
	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (exit_error(2));
	if (init(table, atoi(av[1]), av))
		return (free_n_destroy(table) && exit_error(2));
	if (start_simulation(table))
		return (free_n_destroy(table));
	return (free_n_destroy(table));
}
