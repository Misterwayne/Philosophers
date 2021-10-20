/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truepath <truepath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 19:55:00 by truepath          #+#    #+#             */
/*   Updated: 2021/03/25 18:38:02 by truepath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo_two.h"

void    print_table_struct(t_table *table)
{
    printf("number of philos = %d\n", table->number_of_philos);
    printf("time to die = %d\n", table->time_to_die);
    printf("time to eat = %d\n", table->time_to_eat);
    printf("time to sleep = %d\n", table->time_to_sleep);
    return ;
}

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
    printf("lol");
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

int        set_argv(char **argv, t_table *table)
{
    int i;

    i = -1;
    table->number_of_philos = atoi(argv[1]);
    table->time_to_die = atoi(argv[2]);
    table->time_to_eat = atoi(argv[3]);
    table->time_to_sleep = atoi(argv[4]);
    table->number_of_time_each_must_eat = atoi(argv[5]);
    if (!(table->forks = malloc(sizeof(sem_t) * table->number_of_philos)))
        return (-1);
    while (++i < table->number_of_philos)
        sem_init(&table->forks[i], 0, 1);
    if (!(table->philos = malloc(sizeof(t_philo) * table->number_of_philos)))
        return (-1);
    if (!(memset(table->philos, 0, (sizeof(t_philo) * table->number_of_philos))))
        return (-1);
    return (0);
}

int    load_arg(t_table *table, char **argv)
{
    int i;

    set_argv(argv, table);
    i = -1;
    while (++i < table->number_of_philos)
    {
        
        table->philos[i].number = i;
        table->philos[i].table = table;
        table->philos[i].state = 0;
    }
    return (0);
}

int      main(int argc, char **argv)
{
    t_table         table;
    sem_t           semaphore;
    int             i;

    i = -1;
    load_arg(&table, argv);
    print_table_struct(&table);
    printf("Done");
    while (++i < table.number_of_philos)
    {  
        if (pthread_create(&table.philos[i].threads, NULL, work, &table.philos[i]) != 0)
            return (1);
        printf("Done %d",i);
    }
    i = -1;
    while (++i < table.number_of_philos)
        pthread_join(table.philos[i].threads, NULL);
    printf("Done");
    exit (0);   
}

