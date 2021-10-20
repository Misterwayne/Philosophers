/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truepath <truepath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:03:23 by truepath          #+#    #+#             */
/*   Updated: 2021/03/25 18:28:34 by truepath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/time.h>
#include<pthread.h>
#include<string.h>
#include<semaphore.h>

#define KEY 0x1111

typedef struct      s_philo
{
    struct timeval  start;
    struct timeval  end;
    struct timeval  reset;
    struct timeval  save;
    int             number;
    int             last_meal_time;
    int             state;
    pthread_t       threads;
    struct s_table  *table;
}                   t_philo;

typedef struct      s_table
{
    sem_t           *forks;
    int             number_of_philos;
    int             number_of_time_each_must_eat;
    int             time_to_die;
    int             time_to_sleep;
    int             time_to_eat;
    struct s_philo  *philos;
}                   t_table;
