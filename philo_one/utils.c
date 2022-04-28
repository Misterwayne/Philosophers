/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwane <mwane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 21:05:31 by truepath          #+#    #+#             */
/*   Updated: 2022/04/26 17:05:15 by mwane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int     ft_strlen(char *str)
{
    int i;

    i = 0;
    while(str[i])
        i++;
    return (i);
}

void    error_exit(char *error_msg)
{
    write(2, "Error :", ft_strlen("Error :"));
    write(2, error_msg, ft_strlen(error_msg));
    exit(1);
}

void    check_argv(int argc, char **argv)
{
    int i;

    i = 1;
    if (argc < 4)
        error_exit("too few argument\n");
    while (argv[i] != NULL)
    {
        if (atoi(argv[i]) <= 0)
            error_exit("non numeric argument\n");
        i++;
    }
    return ;
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
