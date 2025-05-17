/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:40:18 by asebban           #+#    #+#             */
/*   Updated: 2025/05/17 19:16:52 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_arg(int ac, char **av)
{
	int	index;
	int	j;

	//philo no more than 200
	if (ac != 5 && ac != 6)
		return (err("Error: Wrong number of arguments\n"));
	index = 1;
	while (index < ac)
	{
		j = 0;
		while (av[index][j])
		{
			if (!ft_isdigit(av[index][j]))
				return (err("Error: Arguments must be positive integers\n"));//./philo +2 80 200 200  //./philo "  2" 80 200 200   //./philo "  2    8" 80 200 200  
			j++;
		}
		if (ft_atoi(av[index]) <= 0)
			return (err("Error: Arguments must be greater than 0\n")); // overflow
		index++;
	}
	return (0);
}

int	init_info(t_info *info, int ac, char **av)
{
	memset(info, 0, sizeof(t_info));
	info->numbers_of_philos = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->must_eat_count = ft_atoi(av[5]);
	else
		info->must_eat_count = -1;
	info->time_start = get_time_start();
	info->someone_died = 0;
	info->all_ate = 0;
	if (init_mutexes(info))
		return (1);
	if (init_philos(info))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (is_valid_arg(ac, av))
		return (ft_usage(), 1);
	if (init_info(&info, ac, av))
        return (ft_clean(&info), 1);

	return (0);
}
