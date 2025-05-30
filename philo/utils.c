/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:04:00 by asebban           #+#    #+#             */
/*   Updated: 2025/05/30 17:50:26 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	long	get_time_start(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static int	skips(const char *str, int *sign)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	long	nbr;
	int		i;
	int		sign;
	long	tmp;

	nbr = 0;
	sign = 1;
	tmp = 0;
	i = skips(str, &sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = nbr;
		nbr = nbr * 10 + str[i] - '0';
		if (nbr / 10 != tmp && sign == 1)
			return (-1);
		else if (nbr / 10 != tmp && sign == -1)
			return (0);
		i++;
	}
	return ((int)nbr * sign);
}

void	print_status(t_philo *philo, char *str)
{
	long long	time;

	if (check_death1(philo))
		return ;
	pthread_mutex_lock(&philo->info->write_lock);
	time = get_time_start() - philo->info->time_start;
	if (philo->info->someone_died != 1)
		printf("%lld %zu %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->info->write_lock);
}

void	smart_sleep(long long time, t_info *info)
{
	long long	start;
	long long	elapsed;

	start = get_time_start();
	while (1)
	{
		elapsed = get_time_start() - start;
		if (elapsed >= time)
			break ;
		pthread_mutex_lock(&info->death_lock);
		if (info->someone_died)
		{
			pthread_mutex_unlock(&info->death_lock);
			break ;
		}
		pthread_mutex_unlock(&info->death_lock);
		usleep(100);
	}
}
