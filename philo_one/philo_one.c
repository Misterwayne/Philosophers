/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truepath <truepath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 20:12:04 by truepath          #+#    #+#             */
/*   Updated: 2021/02/21 22:25:40 by truepath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void    *work(void *argv)
{
    t_philo     *sage;
    long        count;
    int         i;
    
    i = 0;
    sage = argv;
    gettimeofday(&sage->start, NULL);
    gettimeofday(&sage->save, NULL);
    sage->last_meal_time = sage->start.tv_sec;
    while (i < sage->table->number_of_time_each_must_eat)
    {
        gettimeofday(&sage->end, NULL);
        count = (sage->end.tv_sec-sage->start.tv_sec) * 1000000 + sage->end.tv_usec-sage->start.tv_usec;
        if (sage->state == 0)
            philo_eat(sage, count);
        else if (sage->state == 1) // eating
            philo_sleep(sage, count);
        else if (sage->state == 2) // sleep
            philo_think(sage, count);
        else if (sage->last_meal_time >= sage->table->time_to_die || sage->table->number_of_time_each_must_eat == 0)
            philo_dead(sage, count);
    }
    pthread_exit(NULL);
}

int     main(int argc, char **argv)
{
    t_table         table;
    pthread_mutex_t mutex;
    int             i;
    int             j;
    int             k;

    i = -1;
    check_argv(argv);
    load_arg(&table, argv);
    print_table_struct(&table);
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_lock(&mutex);
    while (++i < table.number_of_philos)
        if (pthread_create(&table.philos[i].threads, NULL, work, &table.philos[i]) != 0)
            return (1);
    pthread_mutex_unlock(&mutex);
    i = -1;
    while (++i < table.number_of_philos)
        pthread_join(table.philos[i].threads, NULL);
    printf("Done");
    pthread_mutex_destroy(&mutex);
    free_stuff(&table);
    exit (0);   
}

int    load_arg(t_table *table, char **argv)
{
    int i;

    set_argv(argv, table);
    i = -1;
    while (++i < table->number_of_philos)
    {
        table->philos[i].number = i;
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
    }
    return (0);
}

