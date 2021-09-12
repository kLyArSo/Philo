#include "header.h"

int     min_meal_check(t_philo_data *data)
{
    int i;

    i = 0;
    while (i < game_args->number_of_philosophers)
    {
        if (data[i].meal_counter == game_args->number_of_times_each_philosopher_must_eat)
            i++;
        else
            break ;
    }
    if (i == game_args->number_of_philosophers)
        return (SUCCESS);
    else
        return (FAILURE);
}

int     main(int argc, char **argv)
{
    int i;
    pthread_t           *philosophers;
    t_philo_data        *data;

    i = 0;
    gettimeofday(&start_time, NULL);
    game_args = malloc(sizeof(t_argv));
    if (!game_args)
        return (0);
    set_game_info(game_args);
    philosophers = malloc(game_args->number_of_philosophers * sizeof(pthread_t));
    forks = malloc(game_args->number_of_forks * sizeof(pthread_mutex_t));
    data = malloc(game_args->number_of_philosophers * sizeof(t_philo_data));
    if (!philosophers || !forks || !data)
        return (0);
    set_philo_data(data, game_args);
    forks_init();
    first_wave_deployment(philosophers, data);
    second_wave_deployment(philosophers, data);
    while (min_meal_check(data) != SUCCESS)
        ;
    printf("\n\n\nSUCCESSSS\n\n\n");
    join_the_bunch(philosophers);
    return (0);
}