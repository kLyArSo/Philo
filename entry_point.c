#include "header.h"

void    *entry_point(void   *ptr)
{
    t_philo_data *data;

    while (1)
    {
        data = (t_philo_data *)ptr;
        pthread_mutex_lock(&forks[data->philo_fork_1]);
        pthread_mutex_lock(&forks[data->philo_fork_2]);
        print_status("has taken a fork", data->philo_index);
        print_status("has taken a fork", data->philo_index);

        print_status("is eating", data->philo_index);
        data->meal_counter++;
        data->last_meal = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000)
    - (start_time.tv_sec * 1000 + start_time.tv_usec / 1000);;
        data->next_meal = data->last_meal + game_args->time_to_die;
        usleep(game_args->time_to_eat * 1000);
        pthread_mutex_unlock(&forks[data->philo_fork_1]);
        pthread_mutex_unlock(&forks[data->philo_fork_2]);
        print_status("has dropped a fork", data->philo_index);
        print_status("has dropped a fork", data->philo_index);
        

        print_status("is sleeping", data->philo_index);
        usleep(game_args->time_to_sleep * 1000);
    
        print_status("is thinking", data->philo_index);
    }
    return (NULL);
}