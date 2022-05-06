/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truepath <truepath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:21:22 by bmaudet           #+#    #+#             */
/*   Updated: 2022/05/06 16:56:47 by truepath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(char *str, t_philo *philo)
{
	long int		time;

	time = -1;
	time = get_time() - philo->arg->start_time;
	if (time >= 0 && time <= 2147483647 && !life_status(philo, 0))
		printf("%ld %d %s", time, philo->id, str);
}

void	sleep_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->print);
	status("is sleeping\n", philo);
	pthread_mutex_unlock(&philo->arg->print);
	ft_usleep(philo->arg->s);
	pthread_mutex_lock(&philo->arg->print);
	status("is thinking\n", philo);
	pthread_mutex_unlock(&philo->arg->print);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->print);
	status("is eating\n", philo);
	pthread_mutex_lock(&philo->arg->time_eat);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->arg->time_eat);
	pthread_mutex_unlock(&philo->arg->print);
	ft_usleep(philo->arg->e);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_lock(&philo->arg->print);
	status("has droped a fork\n", philo);
	pthread_mutex_unlock(&philo->arg->print);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_lock(&philo->arg->print);
	status("has droped a fork\n", philo);
	pthread_mutex_unlock(&philo->arg->print);
	sleep_think(philo);
}


void	get_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	pthread_mutex_lock(&philo->arg->print);
	status("has taken a fork\n", philo);
	pthread_mutex_unlock(&philo->arg->print);
	if (!philo->r_fork)
	{
		pthread_mutex_unlock(&philo->l_fork);
		return (ft_usleep(philo->arg->d));
	}
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&philo->arg->print);
	status("has taken a fork\n", philo);
	pthread_mutex_unlock(&philo->arg->print);
	eat(philo);
}

void	*work(void *data)
{
	t_philo					*philo;

	philo = (t_philo *)data;
	while (!life_status(philo, 0))
	{
		live(philo);
		if ((int)++philo->nb_eat == philo->arg->nb_rep)
		{
			pthread_mutex_lock(&philo->arg->finish);
			philo->finish = 1;
			philo->arg->philos_done++;
			if (philo->arg->philos_done == philo->arg->nb)
			{
				pthread_mutex_unlock(&philo->arg->finish);
				life_status(philo, 2);
			}
			else
				pthread_mutex_unlock(&philo->arg->finish);
			return (NULL);
		}
	}
	return (NULL);
}
