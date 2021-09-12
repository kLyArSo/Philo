#include "header.h"

void    print_status(char *str, int x)
{
    int time_stamp;

    pthread_mutex_lock(&mutex);
    gettimeofday(&current_time, NULL);
    time_stamp = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000)
    - (start_time.tv_sec * 1000 + start_time.tv_usec / 1000);
    printf("[%d ms] Philospher %d %s.\n",time_stamp, x + 1, str);
    pthread_mutex_unlock(&mutex);
}

void    set_game_info(t_argv  *game_args)
{
    game_args->number_of_philosophers = 10;
    game_args->number_of_forks = game_args->number_of_philosophers;
    game_args->time_to_die = 250; //in ms
    game_args->time_to_eat = 100; // in ms
    game_args->time_to_sleep = 100; // in ms
    game_args->number_of_times_each_philosopher_must_eat = 1;
}

void    set_philo_data(t_philo_data *data, t_argv  *game_args)
{
    int i;

    i = 0;
    while (i < game_args->number_of_philosophers)
    {
        data[i].philo_index = i;
        if (i == 0)
        {
            data[i].philo_fork_1 = i;
            data[i].philo_fork_2 = game_args->number_of_philosophers - 1;
        }
        else
        {
            data[i].philo_fork_1 = i;
            data[i].philo_fork_2 = i - 1;
        }
        data[i].meal_counter = 0;
        i++;
    }
}