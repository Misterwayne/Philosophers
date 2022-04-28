/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwane <mwane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 20:12:04 by truepath          #+#    #+#             */
/*   Updated: 2022/04/28 15:23:35 by mwane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void    print_msg(t_philo *philo)
{
    long    time;

    pthread_mutex_lock(&philo->table->print);
    time = givetime(philo->og_time);
    if (philo->state == 1)
        printf("%ld ms : philo %d is eating\n", time, philo->number);
    if (philo->state == 2)
        printf("%ld ms : philo %d is sleeping\n", time, philo->number);
    if (philo->state == 0)
        printf("%ld ms : philo %d is thinking\n", time, philo->number);
    if (philo->state == 3)
        printf("%ld ms : philo %d is dead\n", time, philo->number);
    pthread_mutex_unlock(&philo->table->print);
}

void    *work(void *argv)
{
    t_philo     *sage;

    sage = argv;
    gettimeofday(&sage->start, NULL);
    gettimeofday(&sage->save, NULL);
    sage->og_time = givetime(0);
    sage->last_meal_time = sage->og_time;
    while (1)
    {
        if (philo_dead(sage) == 0)
            break ;
        if (sage->state == 0)
            philo_eat(sage);
        if (sage->state == 1)
            philo_sleep(sage);
        if (sage->state == 2)
            philo_think(sage);
    }
    return (NULL);
}

int     main(int argc, char **argv)
{
    t_table         table;
    pthread_mutex_t mutex;
    int             i;

    i = -1;
    check_argv(argc, argv);
    load_arg(argc, &table, argv);
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_lock(&mutex);
    while (++i < table.number_of_philos)
        if (pthread_create(&table.philos[i].threads, NULL, work, &table.philos[i]) != 0)
            return (1);
    pthread_mutex_unlock(&mutex);
    i = -1;
    while (++i < table.number_of_philos)
        pthread_join(table.philos[i].threads, NULL);
    print_table_struct(&table);
    pthread_mutex_destroy(&mutex);
    exit (0);   
}

int    load_arg(int argc, t_table *table, char **argv)
{
    int i;

    set_argv(argc ,argv, table);
    i = -1;
    if (table->number_of_philos > 10)
        table->number_of_philos = 10;
    while (++i < table->number_of_philos)
    {
        table->philos[i].number = i + 1;
        if (i == 0)
            table->philos[i].l_fork = table->number_of_philos - 1;
        else
            table->philos[i].l_fork = i - 1;
        if (i == table->number_of_philos)
            table->philos[i].r_fork = 0;
        else
            table->philos[i].r_fork = i;
        table->philos[i].table = table;
        table->philos[i].state = 0;
        table->philos[i].last_meal_time = 0;
    }
    return (0);
}

