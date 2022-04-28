/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwane <mwane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 20:21:48 by truepath          #+#    #+#             */
/*   Updated: 2022/04/27 17:40:00 by mwane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>

typedef struct      s_philo
{
    struct timeval  start;
    struct timeval  end;
    struct timeval  reset;
    struct timeval  save;
    int             number;
    int             last_meal_time;
    int             l_fork;
    int             r_fork;
    int             state;
    pthread_t       threads;
    struct s_table  *table;
    long            og_time;
}                   t_philo;

typedef struct      s_table
{
    int             number_of_philos;
    int             number_of_time_each_must_eat;
    int             time_to_die;
    int             time_to_sleep;
    int             time_to_eat;
    struct s_philo  *philos;
    pthread_mutex_t *forks;
    pthread_mutex_t print;
}                   t_table;


int                 load_arg(int argc, t_table *table, char **argv);
int                 givetime(long time);
void                print_msg(t_philo *philo);
void                print_states(t_table *table);
int                 eat(t_philo *sage, long count);
void                check_argv(int argc, char **argv);
int                 free_stuff(t_table *table);
void                print_table_struct(t_table *table);
int                 philo_eat(t_philo *sage);
void                philo_sleep(t_philo *sage);
int                 philo_dead(t_philo *sage);
void                philo_think(t_philo *sage);
int                 set_argv(int argc, char **argv, t_table *table);
char			    *ft_itoa(int n);