/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:21:17 by asebban           #+#    #+#             */
/*   Updated: 2025/05/29 12:48:22 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_mutexes(t_info *info)
{
    int i;
    
    info->forks = malloc(sizeof(pthread_mutex_t) * info->numbers_of_philos);
    if (!info->forks)
        return(err("Error: Mutex malloc failed\n"));
    i = 0;
    while (i < info->numbers_of_philos)
    {
        if (pthread_mutex_init(&info->forks[i], NULL))
            return (err("Error: Mutex init failed\n"));
        i++;
    }
    if (pthread_mutex_init(&info->write_lock, NULL))
        return (err("Error: Write mutex init failed\n"));
    if (pthread_mutex_init(&info->meal_lock, NULL))
		return (err("Error: Meal mutex init failed\n"));
	if (pthread_mutex_init(&info->death_lock, NULL))
		return (err("Error: Death mutex init failed\n"));
    return (0);
}

int init_philos(t_info *info)
{
    int i;
    
    info->philos = malloc(sizeof(t_philo) * info->numbers_of_philos);
    if (!info->philos)
        return (err("Error: Philos malloc failed\n"));
    i = 0;
    while (i < info->numbers_of_philos)
    {
        info->philos[i].id = i + 1;
        info->philos[i].meals_eaten = 0;
        info->philos[i].last_meal_time = info->time_start;
        info->philos[i].left_fork = i;
        info->philos[i].right_fork = (i + 1) % info->numbers_of_philos;
        //info->time_start;
        info->philos[i].info = info;
        i++;
    }
    return (0);
}