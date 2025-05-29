/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:40:18 by asebban           #+#    #+#             */
/*   Updated: 2025/05/29 12:34:45 by asebban          ###   ########.fr       */
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
	// memset(info, 0, sizeof(t_info));
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

void	*monitor(void *arg)
{
	t_info	*info;
	int		i;

	info = (t_info *)arg;
	// pthread_mutex_lock(&info->death_lock);
	// while (!info->someone_died)
	// {
	// 	pthread_mutex_unlock(&info->death_lock);
	// 	i = 0;
	// 	while (i < info->numbers_of_philos)
	// 	{
	// 		if (check_death(&info->philos[i], info))
	// 			return (NULL);
	// 		i++;
	// 	}
	// 	if (check_all_ate(info))
	// 		return (NULL);
	// 	usleep(1000);
	// 	pthread_mutex_lock(&info->death_lock);
	// }
	while (1)
	{
		pthread_mutex_lock(&info->death_lock);
		if (info->someone_died)
		{
			pthread_mutex_unlock(&info->death_lock);
			break;
		}
		pthread_mutex_unlock(&info->death_lock);

		i = 0;
		while (i < info->numbers_of_philos)
		{
			if (check_death(&info->philos[i], info))
				return (NULL);
			i++;
		}
		if (check_all_ate(info))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}

int	create_threads(t_info *info)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	while (i < info->numbers_of_philos)
	{
		if (pthread_create(&info->philos[i].thread, NULL, philo_routine, &info->philos[i]))
			return (err("Error: Thread creation failed\n"));
		i++;
	}
	// if (info->numbers_of_philos != 1)
		if (pthread_create(&monitor_thread, NULL, monitor, info))
			return (err("Error: Monitor thread creation failed\n"));
	i = 0;
	while (i < info->numbers_of_philos)
	{
		if (pthread_join(info->philos[i].thread, NULL))
			return (err("Error: Thread join failed\n"));
		i++;
	}
	if (pthread_join(monitor_thread, NULL))
		return (err("Error: Monitor thread join failed\n"));
	return (0);
}

int	main(int ac, char **av)
{
	t_info	*info;

	info = alloc_info();
	if (!info)
		return (ft_usage(), 1); // err() ---> malloc faild
	if (is_valid_arg(ac, av))
		return (ft_usage(), 1);
	if (init_info(info, ac, av))
        return (ft_clean(info), 1);
	if (create_threads(info))
        return (ft_clean(info), 1);
	ft_clean(info);
	return (0);
}
