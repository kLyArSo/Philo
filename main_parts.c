#include "header.h"

void    forks_init()
{
    int i;

    i = 0;
    while (i < game_args->number_of_forks)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
}

void    first_wave_deployment(pthread_t *philosophers, t_philo_data  *data)
{
    int     i;
    void    *ptr;

    i = 0;
    while (i * 2 < game_args->number_of_philosophers)
    {
        ptr = &data[i * 2];
        pthread_create(&philosophers[i * 2], NULL, entry_point, ptr);
        i++;
    }
}

void    second_wave_deployment(pthread_t    *philosophers, t_philo_data *data)
{
    int     i;
    void    *ptr;

    i = 0;
    while (i * 2 + 1 < game_args->number_of_philosophers)
    {
        ptr = &data[i * 2 + 1];
        pthread_create(&philosophers[i * 2 + 1], NULL, entry_point, ptr);
        i++;
    }
}

void    join_the_bunch(pthread_t    *philosophers)
{
    int     i;
    void    *ptr;

    i = 0;
    while (i < game_args->number_of_philosophers)
    {
        pthread_join(philosophers[i], NULL);
        i++;
    }
}
