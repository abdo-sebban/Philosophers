/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:15:17 by asebban           #+#    #+#             */
/*   Updated: 2025/05/27 17:32:17 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	check_death(t_philo *philo, t_info *data)
// {
// 	long long	current_time;
// 	long long	time_since_last_meal;

// 	pthread_mutex_lock(&data->meal_lock);
// 	current_time = get_time();
// 	time_since_last_meal = current_time - philo->last_meal_time;
// 	pthread_mutex_unlock(&data->meal_lock);
	
// 	if (time_since_last_meal >= data->time_to_die)
// 	{
// 		pthread_mutex_lock(&data->death_lock);
// 		if (!data->someone_died)
// 		{
// 			data->someone_died = 1;
// 			pthread_mutex_lock(&data->write_lock);
// 			printf("%lld %d died\n", current_time - data->start_time, philo->id);
// 			pthread_mutex_unlock(&data->write_lock);
// 		}
// 		pthread_mutex_unlock(&data->death_lock);
// 		return (1);
// 	}
// 	return (0);
// }

// int	check_all_ate(t_info *data)
// {
// 	int	i;
// 	int	all_ate;

// 	if (data->must_eat_count == -1)
// 		return (0);
// 	i = 0;
// 	all_ate = 1;
// 	while (i < data->num_philos)
// 	{
// 		pthread_mutex_lock(&data->meal_lock);
// 		if (data->philos[i].meals_eaten < data->must_eat_count)
// 			all_ate = 0;
// 		pthread_mutex_unlock(&data->meal_lock);
// 		if (!all_ate)
// 			break ;
// 		i++;
// 	}
// 	if (all_ate)
// 	{
// 		pthread_mutex_lock(&data->death_lock);
// 		data->someone_died = 1;
// 		pthread_mutex_unlock(&data->death_lock);
// 		return (1);
// 	}
// 	return (0);
// }

// void    *monitor(void *arg)
// {
//     t_info  *info;
//     int     i;

//     info = (t_info *)arg;
//     while (!info->someone_died)
//     {
//         i = 0;
//         while (i < info->numbers_of_philos)
//         {
// 			if (check_death(&info->philos[i], info))
// 				return (NULL);
// 			i++;
// 		}
// 		if (check_all_ate(info))
// 			return (NULL);
// 		usleep(1000);
//     }
//     return (NULL);
// }