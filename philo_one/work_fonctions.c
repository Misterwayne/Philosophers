/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_fonctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwane <mwane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 20:25:27 by truepath          #+#    #+#             */
/*   Updated: 2022/04/28 15:13:40 by mwane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int     philo_eat(t_philo *sage)
{   
    long    time;
    
    pthread_mutex_lock(&sage->table->forks[sage->l_fork]);
    pthread_mutex_lock(&sage->table->forks[sage->r_fork]);
    pthread_mutex_lock(&sage->table->print);
    sage->state = 1;
    if (sage->table->number_of_time_each_must_eat)
        sage->table->number_of_time_each_must_eat -= 1;
    time = givetime(sage->og_time);
    printf("%ld ms : philo %d has taken forks %d and %d\n", time, sage->number, sage->l_fork, sage->r_fork);
    pthread_mutex_unlock(&sage->table->print);
    print_msg(sage);
    usleep(sage->table->time_to_eat * 1000);
    sage->last_meal_time = givetime(0);
    pthread_mutex_lock(&sage->table->print);
    time = givetime(sage->og_time);
    printf("%ld ms : philo %d has droped forks %d and %d\n", time, sage->number, sage->l_fork, sage->r_fork);
    pthread_mutex_unlock(&sage->table->print);
    pthread_mutex_unlock(&sage->table->forks[sage->l_fork]);
    pthread_mutex_unlock(&sage->table->forks[sage->r_fork]);
    return (0);
}

void    philo_sleep(t_philo *sage)
{
    sage->state = 2;
    print_msg(sage);
    usleep(sage->table->time_to_sleep * 1000);
}

int    philo_dead(t_philo *sage)
{
    int i;

    i = 0;
    while (i < sage->table->number_of_philos)
    {
        if (givetime(sage->table->philos[i].last_meal_time) >= sage->table->time_to_die
        || sage->table->number_of_time_each_must_eat == 0)
        {
            sage->state = 3;
            print_msg(sage);
            return (0);
        }
        i++;
    }
    return (1);
}

void    philo_think(t_philo *sage)
{
    sage->state = 0;
    print_msg(sage);
}