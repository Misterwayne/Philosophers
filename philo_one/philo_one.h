/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truepath <truepath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 20:21:48 by truepath          #+#    #+#             */
/*   Updated: 2021/02/21 20:16:32 by truepath         ###   ########.fr       */
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
}                   t_table;


int                 load_arg(t_table *table, char **argv);
void                print_table_struct(t_table *table);
void                print_states(t_table *table);
int                 eat(t_philo *sage, long count);
void                check_argv(char **argv);
int                 free_stuff(t_table *table);
void                print_table_struct(t_table *table);
int                 philo_eat(t_philo *sage, long count);
void                philo_sleep(t_philo *sage, long count);
int                 philo_dead(t_philo *sage, long count);
void                philo_think(t_philo *sage, long count);
int                 set_argv(char **argv, t_table *table);
char			    *ft_itoa(int n);