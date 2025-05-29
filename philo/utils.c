/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:04:00 by asebban           #+#    #+#             */
/*   Updated: 2025/05/29 14:57:02 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

long long get_time_start(void)
{
    struct  timeval tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_atoi(const char *str)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	return ((int)(num * sign));
}


// void	print_status(t_philo *philo, char *str)
// {
// 	long long time;
	
// 	(void )str;
// 	pthread_mutex_lock(&philo->info->write_lock);
// 	time = get_time_start() - philo->info->time_start;
// 	if (!philo->info->someone_died)
// 		printf("%lld %zu %s\n", time, philo->id, str);
// 	pthread_mutex_unlock(&philo->info->write_lock);
// }

// void print_status(t_philo *philo, char *str)
// {
//     long long time;
//     int died;

//     pthread_mutex_lock(&philo->info->death_lock);
//     died = philo->info->someone_died;
//     pthread_mutex_unlock(&philo->info->death_lock);

//     if (!died)
//     {
//         pthread_mutex_lock(&philo->info->write_lock);
//         time = get_time_start() - philo->info->time_start;
//         printf("%lld %zu %s\n", time, philo->id, str);
//         pthread_mutex_unlock(&philo->info->write_lock);
//     }
// }

void print_status(t_philo *philo, char *str)
{
    long long time;
    int died;

    // Check death flag quickly and early
    pthread_mutex_lock(&philo->info->death_lock);
    died = philo->info->someone_died;
    pthread_mutex_unlock(&philo->info->death_lock);

    if (died)
        return; // Someone died, no print

    pthread_mutex_lock(&philo->info->write_lock);
    time = get_time_start() - philo->info->time_start;
    printf("%lld %zu %s\n", time, philo->id, str);
    pthread_mutex_unlock(&philo->info->write_lock);
}



void	smart_sleep(long long time, t_info *info)
{
	long long start;

	start = get_time_start();
	// while (!info->someone_died)
	// {
	// 	if (get_time_start() - start >= time)
	// 		break;
	// 	usleep(100);
	// }
	while (get_time_start() - start < time)
	{
		pthread_mutex_lock(&info->death_lock);
		if (info->someone_died == 0)
		{
			pthread_mutex_unlock(&info->death_lock);	
			break ;
		}
		pthread_mutex_unlock(&info->death_lock);
		usleep(100);
	}
	return ;
}