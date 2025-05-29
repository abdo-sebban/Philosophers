/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 13:46:39 by asebban           #+#    #+#             */
/*   Updated: 2025/05/29 14:50:38 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	take_forks(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->info->forks[philo->left_fork]);
// 	print_status(philo, "has taken a fork");
// 	pthread_mutex_lock(&philo->info->forks[philo->right_fork]);
// 	print_status(philo, "has taken a fork");
// }

void take_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->info->forks[philo->right_fork]);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(&philo->info->forks[philo->left_fork]);
        print_status(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(&philo->info->forks[philo->left_fork]);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(&philo->info->forks[philo->right_fork]);
        print_status(philo, "has taken a fork");
    }
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->meal_lock);
	philo->last_meal_time = get_time_start();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->info->meal_lock);
	print_status(philo, "is eating");
	smart_sleep(philo->info->time_to_eat, philo->info);
}

void    drop_forks(t_philo *philo)
{
    pthread_mutex_unlock(&philo->info->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->info->forks[philo->right_fork]);
	print_status(philo, "is sleeping");
	smart_sleep(philo->info->time_to_sleep, philo->info);
}

void	think(t_philo *philo)
{
	print_status(philo, "is thinking");
}

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->left_fork]);
	print_status(philo, "has taken a fork");
	smart_sleep(philo->info->time_to_die, philo->info);
	pthread_mutex_lock(&philo->info->death_lock);
	philo->info->someone_died = 0;
	pthread_mutex_unlock(&philo->info->death_lock);
}

// void    *philo_routine(void *arg)
// {
//     t_philo *philo;

//     philo = (t_philo *)arg;
//     if (philo->info->numbers_of_philos == 1)
// 	{
// 		one_philo(philo);
// 		return (NULL);
// 	}
//     if (philo->id % 2 == 0)
//         usleep(1000);
//     while (!philo->info->someone_died)
//     {
//         take_forks(philo);
// 		eat(philo);
// 		drop_forks(philo);
// 		think(philo);
//     }
//     return (NULL);
// }


// int check_death(t_info *info)
// {
//     int died;

//     pthread_mutex_lock(&info->death_lock);
//     died = info->someone_died;
//     pthread_mutex_unlock(&info->death_lock);

//     return died;
// }

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->info->numbers_of_philos == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->info->death_lock);
		if (philo->info->someone_died)
		{
			pthread_mutex_unlock(&philo->info->death_lock);
			break;
		}
		pthread_mutex_unlock(&philo->info->death_lock);

		take_forks(philo);
		pthread_mutex_lock(&philo->info->death_lock);
		if (philo->info->someone_died)
		{
			pthread_mutex_unlock(&philo->info->death_lock);
			drop_forks(philo);
			break;
		}
		pthread_mutex_unlock(&philo->info->death_lock);
		eat(philo);
		pthread_mutex_lock(&philo->info->death_lock);
		if (philo->info->someone_died)
		{
			pthread_mutex_unlock(&philo->info->death_lock);
			break;
		}
		pthread_mutex_unlock(&philo->info->death_lock);
		drop_forks(philo);
				pthread_mutex_lock(&philo->info->death_lock);
		if (philo->info->someone_died)
		{
			pthread_mutex_unlock(&philo->info->death_lock);
			break;
		}
		pthread_mutex_unlock(&philo->info->death_lock);
		think(philo);
	}
	return (NULL);
}
