/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:41:04 by asebban           #+#    #+#             */
/*   Updated: 2025/05/17 19:18:32 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> // maybe i dont use this
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
#include <string.h>
#include <stdlib.h>

# define YELLOW  "\033[1;33m"
# define RED "\033[1;31m"
# define RESET   "\033[0m"
# define BLUE    "\033[1;34m"

typedef struct s_philo
{
	size_t				id;
	pthread_t			thread;
	int					meals_eaten;
	long long			last_meal_time;
	int					left_fork;
	int					right_fork;
	struct s_info		*info;
}	t_philo;

typedef struct s_info
{
	int				numbers_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				someone_died;
	int				all_ate;
	long long		time_start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	death_lock;
	t_philo			*philos;
}	t_info;

int		err(char *str);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
void	ft_usage(void);
void    ft_clean(t_info *info);
int		init_philos(t_info *info);
int			init_mutexes(t_info *info);
long long	get_time_start(void);
#endif