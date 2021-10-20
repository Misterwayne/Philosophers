/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truepath <truepath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 21:05:31 by truepath          #+#    #+#             */
/*   Updated: 2021/02/18 22:55:45 by truepath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void    check_argv(char **argv)
{
    if (argv[1] == NULL)
        argv[1] = "3";
    if (argv[2] == NULL)
        argv[2] = "6";
    if (argv[3] == NULL)
        argv[3] = "1";
    if (argv[4] == NULL)
        argv[4] = "1";
    if (argv[5] == NULL)
        argv[5] = "20000000";
    return ;
}

int     free_stuff(t_table *table)
{
    // pthread_mutex_destroy(table->forks);
    // // free(&table->forks);
    return (0);
}

void    print_table_struct(t_table *table)
{
    printf("number of philos = %d\n", table->number_of_philos);
    printf("time to die = %d\n", table->time_to_die);
    printf("time to eat = %d\n", table->time_to_eat);
    printf("time to sleep = %d\n", table->time_to_sleep);
    for (int i = 0; i < table->number_of_philos;i++)
        printf("struct = %d left fork = %d | right fork = %d\n", table->philos[i].number, table->philos[i].l_fork, table->philos[i].r_fork);
    return ;
}

void    print_states(t_table *table)
{
    int i;
    char *state;

    i = 0;
    system("clear");
    while (i < table->number_of_philos)
    {
        if (table->philos[i].state == 0)
            state = "thinking";
        if (table->philos[i].state == 1)
            state = "eating";
        if (table->philos[i].state == 2)
            state = "sleeping";
        if (table->philos[i].state == 3)
            state = "dead";
        printf("philo n°%d | state = %7s | last meal = %d/%d\n",table->philos[i].number, state, table->philos[i].last_meal_time, table->time_to_die);
        i++;
    }
    return ;
}
