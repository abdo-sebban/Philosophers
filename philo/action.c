/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 13:46:39 by asebban           #+#    #+#             */
/*   Updated: 2025/05/30 15:41:38 by asebban          ###   ########.fr       */
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
void eat(t_philo *philo)
{
    t_info *info = philo->info;

    // 1) si quelqu’un est déjà mort (ou tout le monde a fini), on ne fait rien
    pthread_mutex_lock(&info->death_lock);
    if (info->someone_died)
    {
        pthread_mutex_unlock(&info->death_lock);
        return;
    }
    pthread_mutex_unlock(&info->death_lock);

    // 2) puis on mange réellement
    pthread_mutex_lock(&info->meal_lock);
    philo->last_meal_time = get_time_start();
    philo->meals_eaten++;
    // fprintf(stderr,
    //     "DBG-eat: philo %zu just ate meal #%d\n",
    //     philo->id,
    //     philo->meals_eaten);
    // fflush(stderr);
    pthread_mutex_unlock(&info->meal_lock);

    print_status(philo, "is eating");
    smart_sleep(info->time_to_eat, info);
}
// void	eat(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->info->meal_lock);
// 	philo->last_meal_time = get_time_start();
// 	philo->meals_eaten++;
// 	pthread_mutex_unlock(&philo->info->meal_lock);
// 	print_status(philo, "is eating");
// 	smart_sleep(philo->info->time_to_eat, philo->info);
// }

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
int has_eaten_enough(t_philo *philo)
{
    t_info *info = philo->info;
    int enough = 0;
    
    if (info->must_eat_count > 0)
    {
        pthread_mutex_lock(&info->meal_lock);
        enough = (philo->meals_eaten >= info->must_eat_count);
        pthread_mutex_unlock(&info->meal_lock);
    }
    return enough;
}
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
		// pthread_mutex_lock(&philo->info->death_lock);
		// if (philo->info->someone_died)
		// {
		// 	pthread_mutex_unlock(&philo->info->death_lock);
		// 	break;
		// }
		// pthread_mutex_unlock(&philo->info->death_lock);
		drop_forks(philo);
		        
        if (has_eaten_enough(philo))
            break;
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
