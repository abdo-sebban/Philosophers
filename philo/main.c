/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:40:18 by asebban           #+#    #+#             */
/*   Updated: 2025/05/17 14:54:24 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_arg(int ac, char **av)
{
	int	index;
	int	j;

	if (ac != 5 && ac != 6)
		return (err("Error: Wrong number of arguments\n"));
	index = 1;
	while (index < ac)
	{
		j = 0;
		while (av[index][j])
		{
			if (!ft_isdigit(av[index][j]))
				return (err("Error: Arguments must be positive integers\n"));
			j++;
		}
		if (ft_atoi(av[index]) <= 0)
			return (err("Error: Arguments must be greater than 0\n"));
		index++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	// t_info	info;

	if (is_valid_arg(ac, av))
		return (ft_usage(), 1);
}
