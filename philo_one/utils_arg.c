/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truepath <truepath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 22:59:16 by truepath          #+#    #+#             */
/*   Updated: 2021/02/18 23:10:40 by truepath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int        set_argv(char **argv, t_table *table)
{
    int i;

    i = -1;
    table->number_of_philos = atoi(argv[1]);
    table->time_to_die = atoi(argv[2]);
    table->time_to_eat = atoi(argv[3]);
    table->time_to_sleep = atoi(argv[4]);
    table->number_of_time_each_must_eat = atoi(argv[5]);
    if (!(table->forks = malloc(sizeof(pthread_mutex_t) * table->number_of_philos)))
        return (-1);
    while (++i < table->number_of_philos)
        pthread_mutex_init(&table->forks[i], NULL);
    if (!(table->philos = malloc(sizeof(t_philo) * table->number_of_philos)))
        return (-1);
    if (!(memset(table->philos, 0, (sizeof(t_philo) * table->number_of_philos))))
        return (-1);
}