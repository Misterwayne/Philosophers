/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truepath <truepath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 18:28:52 by truepath          #+#    #+#             */
/*   Updated: 2021/03/25 18:31:23 by truepath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int     philo_eat(t_philo *sage, long count)
{
    char    buffer[60];

    sem_wait(sage->table->forks);
    sage->table->number_of_time_each_must_eat -= 1;
    gettimeofday(&sage->reset, NULL);
    sage->last_meal_time = (sage->reset.tv_sec-sage->save.tv_sec) * 1000000 + sage->reset.tv_usec-sage->save.tv_usec;
    sage->state = 1;
    usleep(sage->table->time_to_eat);
    gettimeofday(&sage->save, NULL);
    printf("%ld ms : philo %d is eating\n", count, sage->number);
    write(1, buffer, strlen(buffer));
    sem_post(sage->table->forks);
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
