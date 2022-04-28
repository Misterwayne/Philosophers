/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwane <mwane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 22:59:16 by truepath          #+#    #+#             */
/*   Updated: 2022/04/28 15:15:15 by mwane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int        givetime(long time)
{
    struct timeval      start;
    long                result;

    result = 0;
    gettimeofday(&start,NULL); 
    result = (start.tv_sec * 1000) + (start.tv_usec / 1000);
    result -= time;
    return (result);
}

int        set_argv(int argc, char **argv, t_table *table)
{
    int i;

    i = -1;
    table->number_of_philos = atoi(argv[1]);
    table->time_to_die = atoi(argv[2]);
    table->time_to_eat = atoi(argv[3]);
    table->time_to_sleep = atoi(argv[4]);
    if (argc > 5)
        table->number_of_time_each_must_eat = atoi(argv[5]);
    else
        table->number_of_time_each_must_eat = 1;
    pthread_mutex_init(&table->print, NULL);
    if (!(table->forks = malloc(sizeof(pthread_mutex_t) * table->number_of_philos)))
        return (-1);
    while (++i < table->number_of_philos)
        pthread_mutex_init(&table->forks[i], NULL);
    if (!(table->philos = malloc(sizeof(t_philo) * table->number_of_philos)))
        return (-1);
    if (!(memset(table->philos, 0, (sizeof(t_philo) * table->number_of_philos))))
        return (-1);
    return (0);
}