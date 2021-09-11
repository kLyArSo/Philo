#include "header.h"
#define N 100
#include <sys/time.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t         *forks;
t_argv                  *game_args;
struct timeval current_time;
struct timeval start_time;
void    print_status(char *str, int x)
{
    pthread_mutex_lock(&mutex);
    gettimeofday(&current_time, NULL);
    int time_stamp = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000)
    - (start_time.tv_sec * 1000 + start_time.tv_usec / 1000);
    printf("[%d ms] Philospher %d %s.\n",time_stamp, x + 1, str);
    pthread_mutex_unlock(&mutex);
}

void    set_game_info(t_argv  *game_args)
{
    game_args->number_of_philosophers = 20;
    game_args->number_of_forks = game_args->number_of_philosophers;
    game_args->time_to_die = 12; //in ms
    game_args->time_to_eat = 10; // in ms
    game_args->time_to_sleep = 10; // in ms
    game_args->number_of_times_each_philosopher_must_eat = -1;
}

void    *entry_point(void   *ptr)
{
    int i = 1000;
    t_philo_data *data;

    while (1)
    {
        data = (t_philo_data *)ptr;
        pthread_mutex_lock(&forks[data->philo_fork_1]);
        pthread_mutex_lock(&forks[data->philo_fork_2]);
        print_status("has taken a fork", data->philo_index);
        print_status("has taken a fork", data->philo_index);

        print_status("is eating", data->philo_index);
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
        i++;
    }
}

int     main(int argc, char **argv)
{
    int i;
    void    *ptr;

    
    game_args = malloc(sizeof(t_argv));
    set_game_info(game_args);

    pthread_t           *philosophers = malloc(game_args->number_of_philosophers * sizeof(pthread_t));
    forks = malloc(game_args->number_of_forks * sizeof(pthread_mutex_t));
    i = 0;
    while (i < game_args->number_of_forks)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
    t_philo_data        *data = malloc(game_args->number_of_philosophers * sizeof(t_philo_data));
    set_philo_data(data, game_args);
    i = 0;
    while(i < game_args->number_of_philosophers)
    {
        printf("(philo,fork1,fork2) = (%d,%d,%d)\n"
            ,data[i].philo_index + 1
            ,data[i].philo_fork_1 + 1
            ,data[i].philo_fork_2 + 1);
            i++;
    }

    i = 0;
    gettimeofday(&start_time, NULL);
    while (i < game_args->number_of_philosophers)
    {
        ptr = &data[i];
        pthread_create(&philosophers[i], NULL, entry_point, ptr);
        i++;
    }
    i = 0;
    while (i < game_args->number_of_philosophers)
    {
        pthread_join(philosophers[i], NULL);
        i++;
    }
    return (0);
}