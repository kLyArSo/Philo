#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


typedef struct  s_argv
{
    int number_of_philosophers;
    int number_of_forks;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
}               t_argv;


typedef struct  s_philo_data
{
    int philo_index;
    int philo_fork_1;
    int philo_fork_2;
}               t_philo_data;