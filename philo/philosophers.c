/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:02:55 by smiro             #+#    #+#             */
/*   Updated: 2022/12/06 23:53:06 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_table	*table;

	if (ft_check(ac, av))
		return (exit_error(1));
	if (av[1][0] == '0')
		return (0);
	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (exit_error(2));
	if (init(table, ft_atoi(av[1]), av))
		return (free_n_destroy(table) && exit_error(2));
	if (start_simulation(table))
		return (free_n_destroy(table) && exit_error(2));
	return (free_n_destroy(table));
}
