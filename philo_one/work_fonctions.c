/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_fonctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truepath <truepath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 20:25:27 by truepath          #+#    #+#             */
/*   Updated: 2021/02/19 13:47:53 by truepath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int     philo_eat(t_philo *sage, long count)
{
    char buffer[60];
    
    pthread_mutex_lock(&sage->table->forks[sage->l_fork]);
    pthread_mutex_lock(&sage->table->forks[sage->r_fork]);
    sage->table->number_of_time_each_must_eat -= 1;
    sprintf(buffer, "%ld ms : philo %d has taken forks %d and %d\n", count, sage->number, sage->l_fork, sage->r_fork);
    write(1, buffer, strlen(buffer));
    sprintf(buffer, "%ld ms : philo %d is eating\n", count, sage->number);
    write(1, buffer, strlen(buffer));
    gettimeofday(&sage->reset, NULL);
    sage->last_meal_time = (sage->reset.tv_sec-sage->save.tv_sec) * 1000000 + sage->reset.tv_usec-sage->save.tv_usec;
    sage->state = 1;
    usleep(sage->table->time_to_eat);
    gettimeofday(&sage->save, NULL);
    sprintf(buffer, "%ld ms : philo %d has droped forks %d and %d\n", count, sage->number, sage->l_fork, sage->r_fork);
    write(1, buffer, strlen(buffer));
    pthread_mutex_unlock(&sage->table->forks[sage->l_fork]);
    pthread_mutex_unlock(&sage->table->forks[sage->r_fork]);
    return (0);
}

void    philo_sleep(t_philo *sage, long count)
{
    char buffer[60];

    sprintf(buffer, "%ld ms : philo %d is sleeping\n", count, sage->number);
    write(1, buffer, strlen(buffer));
    sage->state = 2;
    usleep(sage->table->time_to_sleep);
}

int    philo_dead(t_philo *sage, long count)
{
    char buffer[60];

    sprintf(buffer, "%ld ms : philo %d is dead\n", count, sage->number);
    write(1, buffer, strlen(buffer));
    sage->state = 3;
    pthread_exit(NULL);
}

void    philo_think(t_philo *sage, long count)
{
    char buffer[60];

    sprintf(buffer, "%ld ms : philo %d is thinking\n", count, sage->number);
    write(1, buffer, strlen(buffer));
    sage->state = 0;
}